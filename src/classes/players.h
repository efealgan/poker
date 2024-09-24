#ifndef PLAYERS_H
#define PLAYERS_H

#include <iostream>
#include "../utilities.h"
#include "../globals.h"

class Players {
    private:
        int playerID;
        int money;
        int bet;
        
    public:
        int handScore;              //i may not use this.
        int pWideHand[7][2];        //= community + player[id] cards
        int pShortHand[5][2];       //the best evaluated hand of player.
        int pShortHandBuffer[5][2]; //the best evaluated hand 2: electric boogaloo. because i am stupid
        int heldCards[2][2];        //player cards
        int flushCards[7][2];       //we pass this to straight() after a flush so we can check for a straight flush
        
        Players(int id, const int m, const int b);
        
    /// @brief heldCards setter
        /// @param x card slot; 0 -> first slot
        ///                     1 -> second slot            
        /// @param suit [0-3]
        /// @param rank [0-12]
    void setHeldCards(int x, int s, int r);

    ///@brief returns the cards held by the player
        ///@param x card slot; 1 -> first slot 2 -> second slot else -> both slots
    int getHeldCards(int selectedSlot = 0, bool display = false);

    ///@brief deals x cards to the player
    ///@param amountToDeal how many cards to deal
    void dealToPlayer(int amountToDeal);

    //money get set
    int getMoney();
    void setMoney(int m);

    //bet get set
    int getBet();
    void setBet(int b);

    //playerID get
    int getPlayerID() const;

};

#endif //PLAYERS_H