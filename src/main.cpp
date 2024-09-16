#include <iostream>
#include <random>
#include <algorithm>

//local includes
#include "globals.h"
#include "utilities.h"
#include "classes/players.h"
#include "classes/game.h"

/*TODO: this list is roughly based on priority of missing features or existing problems.
    General
        use other files than main.cpp. it's a mess. //only Game class is left
    Game class
        implement duplicate checking
        implement betting 
        implement scoring
        reduce output of hand evaluation
        implement a game loop
        implement a debug mode
        
        a GUI????
*/

int main() {
    initCards();
    listCards();

    Game game;
    game.gameLoop();
    //game.debugMode();
    std::cout << "\nPress Enter to quit.";
    std::cin.get();
    return 0;
    }