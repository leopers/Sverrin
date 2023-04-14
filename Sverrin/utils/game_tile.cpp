#include "game_tile.hpp"

sf::Sprite GameTile::get_sprite() { return sprite; }

GameTile::GameTile(std::string textureName, float x, float y, bool passable, bool enemy = false){
    if(!setTexture(textureName))
        return;
    
    pos = Position(x, y);
    sprite.setPosition(x, y);
    isPassable = passable;
    isEnemy = enemy;
}


bool GameTile::setTexture(std::string textureName){
    if(!texture.loadFromFile(textureName)){
        return false;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
    return true;
}
