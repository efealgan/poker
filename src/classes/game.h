#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <tuple>
#include <stdexcept>
#include <limits>

#include "../globals.h"
#include "players.h"

class Game {
private:
    /**
     * @brief Array of community cards.
     * @note The array is in the form of [suit], [rank].
     * @details The array is initialized to -1, which is an invalid card.
     */
    int communityCards[5][2];
    /**
     * @brief Number of community cards dealt.
     */
    int dealtCommunityCards = 0;
    /**
     * @brief Vector of players.
     */
    std::vector <Players> currentPlayers;
public:
    /**
     * @brief Constructor for the Game class.
     * @param playerCount Number of players to initialize.
     * @details Initializes the players and community cards.
     * @note Please use the default value for playerCount. Defaults can be changed in globals.h.
     */
    Game(int playerCount = PLAYERCOUNT);                                                                       
    /**
     * @brief The main game loop, this is where the game is played.
     * @details This function is the main game loop. It initializes the players, deals the first cards, updates the player hands, deals the community cards, and scores the hands.
     */
    void gameLoop();                                                                                                
    /**
     * @brief A manual, hardcoded debug mode for testing purposes. This is not the final debug mode.
     */
    void debugMode();                                                                                                                  
    /**
     * @brief Sets the community cards for debug mode.
     * @note Input is in the form of suit, rank, suit, rank...
     * @note Updates player hands automatically.
     */
    void setCommunityCards(int s1, int r1, int s2, int r2, int s3, int r3, int s4, int r4, int s5, int r5);
    /**
     * @brief Displays the community cards.
     */
    void displayCommunityCards(); 
    /**
     * @brief Deals the selected amount of community cards.
     * @param amount Amount of community cards to deal.
     */
    void dealCommunityCards(int amount);
    /**
     * @brief Reads the community card at the selected slot.
     * @param selectedSlot (0-4) selects a slot to read.
     * @return Returns the suit and rank of the selected community card.
     */
    int getCommunityCard(int selectedSlot);
    /**
     * @brief [WIP] This function is used to take actions from the players.
     * @details This function is not implemented yet. It will be used to take actions from the players like betting, folding, etc.
     * @todo Implement the function.
     */
    void takeActions();  
    /**
     * @brief Adds newly dealt cards to players' hand.
     * @todo Reset call counter after each game.
     * @note The final array is in the form of [player cards, community cards].
     * @note There is lots of room for optimization.
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
    std::vector<int> flush(int id);
    /**
     * @brief Checks for straight types.
     * @param id ID of the player to check.
     * @param shortHand Is the function called for Royal / Straight Flush?
     * @param flushedCards Vector of cards to check for a Royal / Straight Flush.
     * @return Not organized yet.
     * @todo Organize the return values. And return the high card.
     */
    std::vector<int> straight(int id, bool shortHand = false, std::vector <int> flushedCards = std::vector <int>());
    /**
     * @brief [NOT IMPLEMENTED] Checks for pairs in the player's hand.
     * @todo implement the function
     */
    std::vector<int> duplicate(int id);
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
