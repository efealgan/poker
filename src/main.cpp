#include <iostream>
#include <random>
#include <algorithm>

//local includes
#include "globals.h"
#include "utilities.h"
#include "classes/players.h"
#include "classes/game.h"

/*TODO: 
    this list is roughly based on priority of missing features or existing problems.
    Game class
        straight & flush should return high cards                               //done
            //maybe flush should return all the cards that make the flush
        implement duplicate checking                                            //done
        implement betting 
        implement scoring
        reduce output of hand evaluation
        implement a game loop  //it loops
        implement a debug mode //it kinda exists
        
        a GUI????
*/

int main() {
    initCards();

    Game game;
    game.gameLoop();
    //game.debugMode();
    std::cout << "\nPress Enter to quit.";
    std::cin.get();
    return 0;
    }