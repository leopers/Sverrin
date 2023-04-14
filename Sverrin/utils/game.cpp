#include <iostream>
#include <SFML/System.hpp>
#include "game.hpp"

void wait(int t) {
    sf::Time time = sf::milliseconds(t);
    sf::Clock clock;
    while(clock.getElapsedTime() != time) {}
    return;
}

void Game::initwindow() {
	this->videomode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videomode, "Sverrin", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initfonts() { this->font.loadFromFile("src/ARIAL.ttf"); }

void Game::inittext() {
	this->text1.setFont(this->font);
	this->text1.setFillColor(sf::Color::White);
	this->text1.setCharacterSize(32);

	this->text2.setFont(this->font);
	this->text2.setFillColor(sf::Color::White);
	this->text2.setCharacterSize(20);
	this->text2.setPosition(sf::Vector2f(20, 100));
}

Game::Game() {
	this->initwindow();
	this->initfonts();
	this->inittext();
}

Game::~Game() { delete this->window; }

void Game::open_menu() {
    text1.setString("Seja muito bem-vindo ao Sverryn!!!\n\n");
    text2.setString("Escolha uma opção:\n1. Iniciar jogo \n2. Carregar jogo \n3. Sair \n(digite um número)");

    while (this->window->isOpen()) {
        while(this->window->pollEvent(event)){
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                this->window->close();
                
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                start_game(false);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) 
                start_game(true);            
        }
        window->clear();
        window->draw(text1);
        window->draw(text2);
        window->display();
    }
}

void Game::load_game(GameWorld &gameworld) {
    auto save = std::fstream("save_state.txt", std::ios::in);

    std::string backup_name, backup_class;
    save >> backup_name >> backup_class;

    Status backup_status;
    save >> backup_status.constitution;
    save >> backup_status.dexterity;
    save >> backup_status.intelligence;
    save >> backup_status.strength;
    save >> backup_status.life;
    save >> backup_status.life_base;
    save >> backup_status.spell;

    gameworld.heroe.backup_heroe(backup_name, backup_class, backup_status);

    int x, y;
    save >> x >> y;

    for(int i = 0; i < gameworld.get_gridWidth(); i++)
    for(int j = 0; j < gameworld.get_gridHeight(); j++) {
        bool has_enemy;
        save >> has_enemy;

        if(gameworld.tiles[i][j]->isEnemy && has_enemy == false) {
            gameworld.tiles[i][j]->setTexture("src/grass.png");
            gameworld.tiles[i][j]->isEnemy = false;
        }
    }

    gameworld.playerPos = {x, y};
    gameworld.tiles[0][0]->setTexture("src/grass.png");    
    gameworld.tiles[x][y]->setTexture("src/heroe.png");    
}

void Game::start_game(bool save) {
    GameWorld gameworld = GameWorld();

    if(save) load_game(gameworld);

    while(window->isOpen()) {
        while(window->pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window->close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                auto save = std::fstream("save_state.txt", std::ios::out);
                save << gameworld.heroe.get_name() << '\n'
                << gameworld.heroe.get_character_class() << '\n'
                << gameworld.heroe.get_status().constitution << ' '
                << gameworld.heroe.get_status().dexterity << ' '
                << gameworld.heroe.get_status().intelligence << ' '
                << gameworld.heroe.get_status().strength << ' '
                << gameworld.heroe.get_status().life << ' '
                << gameworld.heroe.get_status().life_base << ' '
                << gameworld.heroe.get_status().spell << '\n'
                << gameworld.playerPos.first << ' '
                << gameworld.playerPos.second << '\n';

                for(int i = 0; i < gameworld.get_gridWidth(); i++) {
                    for(int j = 0; j < gameworld.get_gridHeight(); j++)
                        if(gameworld.tiles[i][j]->isEnemy)
                            save << 1 << ' ';
                        else
                            save << 0 << ' ';

                    save << '\n';
                }

                window->close();
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);

                int x = (localPosition.x / 100);
                int y = (localPosition.y / 100);

                if(gameworld.tiles[x][y]->isPassable == true) {
                    auto path = gameworld.dijkstra({gameworld.playerPos.first, gameworld.playerPos.second}, {x, y});

                    while(path.is_empty() == false) {
                        gameworld.tiles[gameworld.playerPos.first][gameworld.playerPos.second]->setTexture("src/grass.png");

                        auto u = path.top();
                        path.pop();

                        if(gameworld.tiles[u.first][u.second]->isEnemy)
                        if(start_battle(gameworld)) {
                            gameworld.playerPos = {u.first, u.second};
                            gameworld.tiles[u.first][u.second]->setTexture("src/heroe.png");
                            gameworld.tiles[u.first][u.second]->isEnemy = false;
                            break;
                        }
                        else
                            window->close();

                        gameworld.playerPos = {u.first, u.second};
                        gameworld.tiles[u.first][u.second]->setTexture("src/heroe.png");

                        window->clear();
                        for(int i = 0; i < gameworld.get_gridWidth(); i++)
                        for(int j = 0; j < gameworld.get_gridHeight(); j++)
                            window->draw(gameworld.tiles[i][j]->get_sprite());
                        window->display();

                        wait(500);
                    }
                }
            }
        }

        window->clear();
        for(int i = 0; i < gameworld.get_gridWidth(); i++)
        for(int j = 0; j < gameworld.get_gridHeight(); j++)
            window->draw(gameworld.tiles[i][j]->get_sprite());
        window->display();

    }
    window->clear();
                
}

bool Game::start_battle(GameWorld &gameworld) {
    Character enemy;
    Character::create_enemy(enemy);

    while(this->window->isOpen()) {
        window->clear();
        
        text1.setString(gameworld.heroe.get_name() + " vs " + enemy.get_name() + "\n\n");
        window->draw(text1);

        text2.setString(std::to_string(gameworld.heroe.get_status().life) + " / " + std::to_string(gameworld.heroe.get_status().life_base) + "         " + std::to_string(enemy.get_status().life) + " / " + std::to_string(enemy.get_status().life_base) + "\n\n Escolha sua ação:\n1.Atacar\n2.Usar magia\n3.Atordoar\n4. Desistir");
        window->draw(text2);

        window->display();

        if(enemy.get_status().life < 0) {
            wait(500);
            return true;
        }
        if(gameworld.heroe.get_status().life < 0) {
            wait(500);
            return false;
        }
        
        while(this->window->pollEvent(event)) {

            if(sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
                this->window->close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                enemy.attack(gameworld.heroe);

                std::mt19937 gen(enemy.dev());
                std::uniform_int_distribution<int> d2(1,2);
                if(d2(gen) == 1)
                    gameworld.heroe.attack(enemy);
                else 
                    enemy.heal();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                gameworld.heroe.heal();

                std::mt19937 gen(enemy.dev());
                std::uniform_int_distribution<int> d2(1,2);
                if(d2(gen) == 1)
                    gameworld.heroe.attack(enemy);
                else 
                    enemy.heal();
            }
            
        }
    }

    return true;
}
