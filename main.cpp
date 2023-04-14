#include "game.hpp"

int main(){
    Game game;
    game.open_menu();
    game.~Game();
    return 0;
}
