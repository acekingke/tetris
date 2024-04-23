#include <ncurses.h>
#include <time.h>
#include <iostream>
#include "game.hpp"

using namespace std;

int main(int argc, char *argv[]) {
   
    auto game = new Game();
   game->run();
    //game->Test();
    delete game;

    return 0;
}