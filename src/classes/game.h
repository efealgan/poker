#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../globals.h"
#include "players.h"

class Game {
private:
    int communityCards[5][2];
    int dealtCommunityCards = 0;
    std::vector <int> flushedCards;
    std::vector <Players> currentPlayers;
public:

    Game(int playerCount = PLAYERCOUNT);                                                                            //game constructor

    void gameLoop();                                                                                                
    void debugMode();                                                                                                                  
    void setCommunityCards(int s1, int r1, int s2, int r2, int s3, int r3, int s4, int r4, int s5, int r5);
    void displayCommunityCards();                                        
    void dealCommunityCards(int amount);
    int getCommunityCard(int x);
    void takeActions();  
    /**
     * @brief Adds newly dealt cards to players' hand.
     * @todo Reset call counter after each game.
    */
    void updatePlayerHands();
    /**
     * @brief [WIP] Scores the players' hands.
     * @details Calls scoring functions in correct order.
     */
    void scoreHands();
    /**
     * @brief Checks for a flush in the player's hand.
     * @param id ID of the player to check.
     * @return return values are a mess
     * @details Checks for Flush, Straight Flush, and Royal Flush.
     * @note Checking for Straight Flush and Royal Flush calls the straight() function.
     * @todo return values should be organized, in case of a flush should return the ranks
     */
    int flush(int id);
    /**
     * @brief Checks for straight types.
     * @param id ID of the player to check.
     * @param shortHand Is the function called for Royal / Straight Flush?
     * @param flushedCards Vector of cards to check for a Royal / Straight Flush.
     * @return Not organized yet.
     * @todo Organize the return values. And return the high card.
     */
    int straight(int id, bool shortHand = false, std::vector <int> flushedCards = std::vector <int>());
    /**
     * @brief [NOT IMPLEMENTED] Checks for pairs in the player's hand.
     * @todo implement the function
     */
    int duplicate(int id);
    /**
     * @brief Displays the player's hand including the community cards.
     * @param id ID of the player to display.
     */
    void displayHand(int id);
    /**
     * @brief Deals the first two cards to each player.
     */
    void dealFirstCards();
    /**
     * @brief Prints the player's data.
     * @param playerID ID of the player to display.
     */
    void displayPlayerData(int playerID = -1);

    /**
     * @brief This function is used to find a player by their ID.
     * @param id ID of the player to find.
     * @return Returns a pointer to the player with the specified ID.
    */
    Players* findPlayerByID(int id);

};

#endif










