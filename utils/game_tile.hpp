#pragma once

#include <utility>
#include <string>
#include <SFML/Graphics.hpp>

using Position = std::pair<int, int>;

class GameTile {
public:
    GameTile(std::string, float, float, bool, bool);
    bool isPassable;
    bool isEnemy;
    bool setTexture(std::string);

    sf::Sprite get_sprite();
    
private:
    Position pos;
    sf::Texture texture;
    sf::Sprite sprite;
};
