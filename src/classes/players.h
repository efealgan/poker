#ifndef PLAYERS_H
#define PLAYERS_H

#include <iostream>
#include "../utilities.h"
#include "../globals.h"


class Players {
private:
    int playerID;               //this ID is static, adding or removing players does not change existing players' ID
    int money;                  //current player money //default in globals.h
    int bet;                    //current player bet   //default in globals.h
        
public:
    int handScore;              //NOT USED //this might be useful for a future feature when determining the winner
    int pWideHand[7][2];        //= player cards + community cards
    int pShortHand[5][2];       //the best evaluated hand of player.
    int pShortHandBuffer[5][2]; //the best evaluated hand 2: electric boogaloo. because i am stupid
    int heldCards[2][2];        //player cards
    int flushCards[7][2];       //we pass this to straight() after a flush so we can check for a straight flush
    /// @brief player constructor
    /// @param id static id of the player
    /// @param m  starting money
    /// @param b  starting bet (should be 0)
    Players(int id, const int m, const int b);
        
    //cards get set

    /// @brief heldCards setter
    /// @param selectedSlot card slot:  1 -> first slot
    ///                                 2 -> second slot            
    /// @param suitValue [0-3]
    /// @param rankValue [0-12]
    void setHeldCards(int selectedSlot, int suitValue, int rankValue);
    ///@brief held cards getter
    ///@param selectedSlot card slot; 1 -> first slot, 2 -> second slot, else -> both slots)
    ///@param display if true, displays the cards dealt. 
    ///@return [CONST] returns the cards held by the player
    int getHeldCards(int selectedSlot = 0, bool display = false) const;

    
    //money
    ///@brief money getter for the passed player
    ///@return [CONST] returns the current money of the player
    int getMoney() const;
    ///@brief money setter for the passed player
    ///@param newMoney the amount of money to set
    void setMoney(int newMoney);

    //bet
    ///@brief bet getter for the passed player
    ///@return [CONST] returns the current bet of the player
    int getBet() const;
    ///@brief bet setter for the passed player
    ///@param newBet the amount of bet to set
    void setBet(int newBet);

    //playerID
    ///@brief playerID getter for the passed player
    ///@return [CONST] returns the playerID of the player
    int getPlayerID() const;

    ///@brief deals and sets the selected amount of cards to the player
    ///@param amountToDeal how many cards to deal
    void dealToPlayer(int amountToDeal);

};

#endif //PLAYERS_H