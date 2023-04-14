#pragma once
#include <SFML/Graphics.hpp>
#include "game_world.hpp"

class Game {
private:
    sf::RenderWindow* window;
    sf::VideoMode videomode;
    sf::Text text1, text2;
    sf::Font font;
    sf::Event event;

    void initwindow();
    void initfonts();
    void inittext();

    void start_game(bool);
    void load_game(GameWorld &);
    bool start_battle(GameWorld &);

public:
    Game();
    ~Game();
    void open_menu();
};
