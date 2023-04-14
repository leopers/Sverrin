#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "game_tile.hpp"
#include "stack.hpp"
#include "character.hpp"

class GameWorld{
public:
    GameWorld();
    void setUpInitialState();
    void setUpTiles();
    Stack<Position> dijkstra(Position, Position);

    int get_gridWidth();
    int get_gridHeight();

    std::vector<std::vector<std::shared_ptr<GameTile>>> tiles;
    Position playerPos;
    Character heroe;
private:
    int gridWidth;
    int gridHeight;
};
