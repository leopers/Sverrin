#include "game_world.hpp"
#include "priority_queue.hpp"
#include <array>

int GameWorld::get_gridWidth() { return gridWidth; }

int GameWorld::get_gridHeight() { return gridHeight; }

GameWorld::GameWorld(){
    gridHeight = 6; 
    gridWidth = 8;
    playerPos = {0, 0};
    setUpInitialState();
    setUpTiles();

    Character::create_heroe(heroe);
}

void GameWorld::setUpInitialState() {
    playerPos = Position(0,0);
}

void GameWorld::setUpTiles(){
    tiles.clear();
    std::vector<std::shared_ptr<GameTile>> firstRow;
    firstRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/heroe.png", 0, 0, true, false)));
    firstRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 0, 100, false, false)));
    firstRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 0, 200, true, false)));
    firstRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 0, 300, false, false)));
    firstRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 0, 400, true, false)));
    firstRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 0, 500, true, false)));
    tiles.push_back(firstRow);

    std::vector<std::shared_ptr<GameTile>> secondRow;
    secondRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 100, 0, true, false)));
    secondRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 100, 100, true, false)));
    secondRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/enemy.png", 100, 200, true, true)));
    secondRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 100, 300, true, false)));
    secondRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/enemy.png", 100, 400, true, true)));
    secondRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 100, 500, true, false)));
    tiles.push_back(secondRow);

    std::vector<std::shared_ptr<GameTile>> thirdRow;
    thirdRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 200, 0, true, false)));
    thirdRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 200, 100, false, false)));
    thirdRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 200, 200, false, false)));
    thirdRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 200, 300, true, false)));
    thirdRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 200, 400, false, false)));
    thirdRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 200, 500, true, false)));
    tiles.push_back(thirdRow);

    std::vector<std::shared_ptr<GameTile>> fourthRow;
    fourthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 300, 0, true, false)));
    fourthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/enemy.png", 300, 100, true, true)));
    fourthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 300, 200, true, false)));
    fourthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 300, 300, true, false)));
    fourthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 300, 400, false, false)));
    fourthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 300, 500, true, false)));
    tiles.push_back(fourthRow);

    std::vector<std::shared_ptr<GameTile>> fithRow;
    fithRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 400, 0, false, false)));
    fithRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 400, 100, false, false)));
    fithRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 400, 200, false, false)));
    fithRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/enemy.png", 400, 300, true, true)));
    fithRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 400, 400, true, false)));
    fithRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/enemy.png", 400, 500, true, true)));
    tiles.push_back(fithRow);

    std::vector<std::shared_ptr<GameTile>> sixthRow;
    sixthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/enemy.png", 500, 0, true, true)));
    sixthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 500, 100, true, false)));
    sixthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 500, 200, true, false)));
    sixthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 500, 300, true, false)));
    sixthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 500, 400, false, false)));
    sixthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 500, 500, true, false)));
    tiles.push_back(sixthRow);

    std::vector<std::shared_ptr<GameTile>> seventhRow;
    seventhRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 600, 0, true, false)));
    seventhRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 600, 100, false, false)));
    seventhRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 600, 200, false, false)));
    seventhRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 600, 300, true, false)));
    seventhRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/wall.png", 600, 400, false, false)));
    seventhRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 600, 500, true, false)));
    tiles.push_back(seventhRow);

    std::vector<std::shared_ptr<GameTile>> eighthRow;
    eighthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 700, 0, true, false)));
    eighthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 700, 100, true, false)));
    eighthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 700, 200, true, false)));
    eighthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/enemy.png", 700, 300, true, true)));
    eighthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 700, 400, true, false)));
    eighthRow.push_back(std::shared_ptr<GameTile>(new GameTile("src/grass.png", 700, 500, true, false)));
    tiles.push_back(eighthRow);
}

Stack<Position> GameWorld::dijkstra(Position origin, Position destiny) {
    std::array<std::array<int, 8>, 6> dist;
    std::array<std::array<Position, 8>, 6> predecessor;
    std::array<std::array<bool, 8>, 6> visited;
    for(int i = 0; i < gridWidth; i++)
    for(int j = 0; j < gridHeight; j++)
        dist[i][j] = -1, predecessor[i][j] = {-1, -1}, visited[i][j] = false;

    dist[origin.first][origin.second] = 0;

    Priority_Queue<std::pair<int, Position>> pqueue;
    pqueue.enqueue({0, {origin.first, origin.second}});

    std::array<int, 4> dx = {1, 0, -1, 0};
    std::array<int, 4> dy = {0, 1, 0, -1};

    while(pqueue.size() > 0) {
        auto top = pqueue.dequeue();
        auto u = top.second;

        if(visited[u.first][u.second] == false) {
            visited[u.first][u.second] = true;

            for(int i = 0; i < 4; i++) {
                Position v = {u.first + dx[i], u.second + dy[i]};
                if(v.first >= gridWidth || v.first < 0 || v.second >= gridHeight || v.second < 0 || tiles[v.first][v.second]->isPassable == false)
                    continue;

                int enemy = 0;
                if(tiles[v.first][v.second]->isEnemy) enemy++;

                if(dist[v.first][v.second] == -1 || dist[v.first][v.second] > dist[u.first][u.second] + enemy) {
                    dist[v.first][v.second] = dist[u.first][u.second] + enemy;
                    predecessor[v.first][v.second] = {u.first, u.second};
                    pqueue.enqueue({dist[v.first][v.second], {v.first, v.second}});
                }
            }
        }
    }

    Stack<Position> path;
    while(destiny != origin) {
        path.push(destiny);
        destiny = predecessor[destiny.first][destiny.second];
    }

    return path;
}
