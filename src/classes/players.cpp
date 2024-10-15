#include "players.h"

//please refer to the header file for documentation
Players::Players(int id, const int startingMoney, const int startingBet) {
    playerID = id;
    money = startingMoney;
    bet = startingBet;
    heldCards[0][0] = -1;
    heldCards[0][1] = -1;
    heldCards[1][0] = -1;
    heldCards[1][1] = -1;
    score.push_back(-1);
    std::cout << "Player " << playerID + 1 << " has been initialized with " << 
    money << " credits. ID = " << playerID << ".\n";
}

void Players::setHeldCards(int selectedSlot, int suitValue, int rankValue) {
    if (selectedSlot == 1) // first card is selected
    {
        this->heldCards[0][0] = suitValue;
        this->heldCards[0][1] = rankValue;
        std::cout << "Player " << this->playerID << " has been dealt: "; 
        displayCard(heldCards[0][0], heldCards[0][1]);
        std::cout << std::endl;
    }
    else if (selectedSlot == 2) // second card is selected 
    {
        this->heldCards[1][0] = suitValue;
        this->heldCards[1][1] = rankValue;
        std::cout << "Player " << this->playerID << " has been dealt: "; 
        displayCard(heldCards[1][0], heldCards[1][1]);
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Invalid card slot.\n";
    }
}
int Players::getHeldCards(int selectedSlot, bool display) const {
    int id = this->playerID;
    if (selectedSlot == 1) {
        if (display == true){
            std::cout << "Player " << id + 1 << " has the following card on the first slot: ";
            displayCard(heldCards[0][0], heldCards[0][1]);
            std::cout << std::endl;
        }
        return heldCards[0][0], heldCards[0][1];
    }
    else if (selectedSlot == 2) {
        if (display == true){
            std::cout << "Player " << id + 1 << " has the following card on the second slot: ";
            displayCard(heldCards[1][0], heldCards[1][1]);
            std::cout << std::endl;
        }
        return heldCards[1][0], heldCards[1][1];
    }
    else {
        if (display == true){
            std::cout << "Player " << id + 1 << " has the cards: ";
            displayCard(heldCards[0][0], heldCards[0][1]);
            std::cout << " and ";
            displayCard(heldCards[1][0], heldCards[1][1]);
            std::cout << std::endl;
        }
        return heldCards[0][0], heldCards[0][1], heldCards[1][0], heldCards[1][1];
    }
}

int Players::getMoney() const {
    return this->money;
}
void Players::setMoney(int newMoney) {
    this->money = newMoney;
}

int Players::getBet() const {
    return this->bet;
}
void Players::setBet(int newBet) {
    this->bet = newBet;
}

int Players::getPlayerID() const {
    return this->playerID;
}

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

void Players::testNewScore(std::vector <int> newScore) {
    if (this->score[0] <= newScore[0]){
        this->score = newScore;
        std::cout << "New best score is: " << this->score[0] << ".\n";
    }
    else {
        std::cout << "Previous score (" << this->score[0] << ") was better. Not changing score to " << newScore[0] << ".\n";
    }
}

std::vector <int> Players::getPlayerScore(){
    return this->score;
}













