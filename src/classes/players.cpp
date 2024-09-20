#include "players.h"

/// @brief player constructor
/// @param id static id of the player
/// @param m  starting money
/// @param b  starting bet (should be 0)
Players::Players(int id, const int m, const int b) {
    playerID = id;
    money = PLAYERMONEY;
    bet = PLAYERBET;
    heldCards[0][0] = -1;
    heldCards[0][1] = -1;
    heldCards[1][0] = -1;
    heldCards[1][1] = -1;
    std::cout << "Player " << playerID << " has been initialized with " << 
    money << " money, " << 
    bet << " bet, and has no cards dealt yet.\n";
}

/// @brief heldCards setter
/// @param x card slot; 0 -> first slot
///                     1 -> second slot            
/// @param suit [0-3]
/// @param rank [0-12]
void Players::setHeldCards(int x, int s, int r) {
    if (x == 1) // first card is selected
    {
        this->heldCards[0][0] = s;
        this->heldCards[0][1] = r;
        std::cout << "Player " << this->playerID << " has been dealt: "; 
        displayCard(heldCards[0][0], heldCards[0][1]);
        std::cout << std::endl;
    }
    else if (x == 2) // second card is selected 
    {
        this->heldCards[1][0] = s;
        this->heldCards[1][1] = r;
        std::cout << "Player " << this->playerID << " has been dealt: "; 
        displayCard(heldCards[1][0], heldCards[1][1]);
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Invalid card slot.\n";
    }
}

///@brief held cards getter
///@param selectedSlot card slot; 1 -> first slot, 2 -> second slot, else -> both slots)
///@param display if true, displays the cards dealt. 
///@return returns the cards held by the player
int Players::getHeldCards(int selectedSlot, bool display) {
    int id = this->playerID;
    if (selectedSlot == 1) {
        if (display == true){
            std::cout << "Player " << id << " has the following card on the first slot: ";
            displayCard(heldCards[0][0], heldCards[0][1]);
            std::cout << std::endl;
        }
        return heldCards[0][0], heldCards[0][1];
    }
    else if (selectedSlot == 2) {
        if (display == true){
            std::cout << "Player " << id << " has the following card on the second slot: ";
            displayCard(heldCards[1][0], heldCards[1][1]);
            std::cout << std::endl;
        }
        return heldCards[1][0], heldCards[1][1];
    }
    else {
        if (display == true){
            std::cout << "Player " << id << " has the cards: ";
            displayCard(heldCards[0][0], heldCards[0][1]);
            std::cout << " and ";
            displayCard(heldCards[1][0], heldCards[1][1]);
            std::cout << std::endl;
        }
        return heldCards[0][0], heldCards[0][1], heldCards[1][0], heldCards[1][1];
    }
}

///@brief deals x cards to the player
///@param amountToDeal how many cards to deal
void Players::dealToPlayer(int amountToDeal) {
    for (int i = 0; i < amountToDeal; i++) {
        if (this->heldCards[0][0] == -1 && this->heldCards[0][1] == -1) {
            dealCard(1);
            this->setHeldCards(1, dealtSuit, dealtRank); //dealt the first card
        }
        else if (this->heldCards[1][0] == -1 && this->heldCards[1][1] == -1) {
            dealCard(1);
            this->setHeldCards(2, dealtSuit, dealtRank); //dealt the second card
        }
        
        else {
            std::cout << "Player " << this->playerID << " already has 2 cards dealt.\n";
            break;
        }
    }

}

int Players::getMoney() {
    return this->money;
}

void Players::setMoney(int m) {
    this->money = m;
}

int Players::getBet() {
    return this->bet;
}

void Players::setBet(int b) {
    this->bet = b;
}

int Players::getPlayerID() const {
    return this->playerID;
}


















