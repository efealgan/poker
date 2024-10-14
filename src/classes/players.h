#ifndef PLAYERS_H
#define PLAYERS_H

#include <vector>
#include <iostream>
#include "../utilities.h"
#include "../globals.h"

/**
 * @class Players
 * @brief This class creates and manages players.
 * @details Manages player-specific data such as money, bet, and cards.
*/
class Players {
private:
    int playerID;               //Static ID of player, adding or removing players does not change existing players' ID
    int money;                  //current player money
    int bet;                    //current player bet
        
public:
    int handScore;              //NOT USED //this might be useful for a future feature when determining the winner
    int pWideHand[7][2];        //= player cards + community cards
    int pShortHand[5][2];       //the best evaluated hand of player.
    int pShortHandBuffer[5][2]; //the best evaluated hand 2: electric boogaloo. because i am stupid
    int heldCards[2][2];        //player cards
    int flushCards[7][2];       //we pass this to straight() after a flush so we can check for a straight flush
    std::vector <int> score;    //the best evaluated hand of the player.
    /**
     * @brief Constructor for the Players class.
     * @param id Static id of the player.
     * @param m  Starting money for the player.
     * @param b  Starting bet for the player.
    */
    Players(int id, const int m, const int b);

    // cards
    /**
     * @brief Sets the held cards for the player.
     * @param selectedSlot Card slot:  1 -> first slot
     *                                 2 -> second slot
     * @param suitValue [0-3] New suit value for the card.
     * @param rankValue [0-12] New rank value for the card.
     */
    void setHeldCards(int selectedSlot, int suitValue, int rankValue);
    /**
     * @brief Gets the held cards for the player.
     * @param selectedSlot Card slot:  1 -> first slot
     *                                 2 -> second slot
     *                                 else -> both slots
     * @param display If true, displays the cards dealt.
     * @return Returns the cards held by the player.
     */
    int getHeldCards(int selectedSlot = 0, bool display = false) const;

    //money
    /**
     * @brief Money getter for the passed player.
     * @return [CONST] Returns the current money of the player.
     */
    int getMoney() const;
    /**
     * @brief Money setter for the passed player.
     * @param newMoney The amount of money to set.
     */
    void setMoney(int newMoney);

    //bet
    /** 
     * @brief bet getter for the passed player
     * @return [CONST] returns the current bet of the player
    */
    int getBet() const;
    /**
     * @brief Bet setter for the passed player.
     * @param newBet The amount of bet to set
    */
    void setBet(int newBet);

    //playerID
    /**
     * @brief playerID getter for the passed player
     * @return [CONST] returns the playerID of the player
     */
    int getPlayerID() const;

    /**
     * @brief Deals the selected amount of cards to the player.
     * @param amountToDeal How many cards to deal.
     */
    void dealToPlayer(int amountToDeal);

};

#endif //PLAYERS_H