#include "utilities.h"


void displaySuit(int suit, bool capitalize, bool plural) {
    switch (capitalize){
        case true:
            switch (plural){
                case true:
                    switch (suit){
                        case 0: 
                            std::cout << "Spades";
                            break;
                        case 1:
                            std::cout << "Clubs";
                            break;
                        case 2:
                            std::cout << "Hearts";
                            break;
                        case 3:
                            std::cout << "Diamonds";
                            break;
                    }
                    break;
                case false:
                    switch (suit){
                        case 0: 
                            std::cout << "Spade";
                            break;
                        case 1:
                            std::cout << "Club";
                            break;
                        case 2:
                            std::cout << "Heart";
                            break;
                        case 3:
                            std::cout << "Diamond";
                            break;
                    }
                    break;
            }
            break;

        case false:
            switch (plural){
                case true:
                    switch (suit){
                        case 0: 
                            std::cout << " spades";
                            break;
                        case 1:
                            std::cout << " clubs";
                            break;
                        case 2:
                            std::cout << " hearts";
                            break;
                        case 3:
                            std::cout << " diamonds";
                            break;
                    }
                    break;
                case false:
                    switch (suit){
                        case 0: 
                            std::cout << " spade";
                            break;
                        case 1:
                            std::cout << " club";
                            break;
                        case 2:
                            std::cout << " heart";
                            break;
                        case 3:
                            std::cout << " diamond";
                            break;
                    }
                    break;
            }
            break;
    }
}
void displayRank(int rank, bool longForm, bool capitalize, bool plural){
    switch (longForm){
        case true:
            switch (capitalize){
                case true:
                    switch (plural){
                        case true:
                            switch (rank){
                                case 0: 
                                    std::cout << "Aces";
                                    break;
                                case 1:
                                    std::cout << "Twos";
                                    break;
                                case 2:
                                    std::cout << "Threes";
                                    break;
                                case 3:
                                    std::cout << "Fours";
                                    break;
                                case 4:
                                    std::cout << "Fives";
                                    break;
                                case 5:
                                    std::cout << "Sixes";
                                    break;
                                case 6:
                                    std::cout << "Sevens";
                                    break;
                                case 7:
                                    std::cout << "Eights";
                                    break;
                                case 8:
                                    std::cout << "Nines";
                                    break;
                                case 9:
                                    std::cout << "Tens";
                                    break;
                                case 10:
                                    std::cout << "Jacks";
                                    break;
                                case 11:
                                    std::cout << "Queens";
                                    break;
                                case 12:
                                    std::cout << "Kings";
                                    break;      
                            }
                            break;
                        case false:
                            switch (rank){
                            case 0: 
                                std::cout << "Ace";
                                break;
                            case 1:
                                std::cout << "Two";
                                break;
                            case 2:
                                std::cout << "Three";
                                break;
                            case 3:
                                std::cout << "Four";
                                break;
                            case 4:
                                std::cout << "Five";
                                break;
                            case 5:
                                std::cout << "Six";
                                break;
                            case 6:
                                std::cout << "Seven";
                                break;
                            case 7:
                                std::cout << "Eight";
                                break;
                            case 8:
                                std::cout << "Nine";
                                break;
                            case 9:
                                std::cout << "Ten";
                                break;
                            case 10:
                                std::cout << "Jack";
                                break;
                            case 11:
                                std::cout << "Queen";
                                break;
                            case 12:
                                std::cout << "King";
                                break;      
                        }
                            break;
                    }
                    break;
                case false:
                    switch (plural){
                        case true:
                            switch (rank){
                                case 0: 
                                    std::cout << "Aces";
                                    break;
                                case 1:
                                    std::cout << "Twos";
                                    break;
                                case 2:
                                    std::cout << "Threes";
                                    break;
                                case 3:
                                    std::cout << "Fours";
                                    break;
                                case 4:
                                    std::cout << "Fives";
                                    break;
                                case 5:
                                    std::cout << "Sixes";
                                    break;
                                case 6:
                                    std::cout << "Sevens";
                                    break;
                                case 7:
                                    std::cout << "Eights";
                                    break;
                                case 8:
                                    std::cout << "Nines";
                                    break;
                                case 9:
                                    std::cout << "Tens";
                                    break;
                                case 10:
                                    std::cout << "Jacks";
                                    break;
                                case 11:
                                    std::cout << "Queens";
                                    break;
                                case 12:
                                    std::cout << "Kings";
                                    break;      
                            }
                            break;
                        case false:
                            switch (rank){
                                case 0: 
                                    std::cout << "Ace";
                                    break;
                                case 1:
                                    std::cout << "Two";
                                    break;
                                case 2:
                                    std::cout << "Three";
                                    break;
                                case 3:
                                    std::cout << "Four";
                                    break;
                                case 4:
                                    std::cout << "Five";
                                    break;
                                case 5:
                                    std::cout << "Six";
                                    break;
                                case 6:
                                    std::cout << "Seven";
                                    break;
                                case 7:
                                    std::cout << "Eight";
                                    break;
                                case 8:
                                    std::cout << "Nine";
                                    break;
                                case 9:
                                    std::cout << "Ten";
                                    break;
                                case 10:
                                    std::cout << "Jack";
                                    break;
                                case 11:
                                    std::cout << "Queen";
                                    break;
                                case 12:
                                    std::cout << "King";
                                    break;      
                    }
                            break;
                    }
                    break;
            }
            break;
        case false:
            //capitalizing short form is useless, so i didnt put the switch for it.
            switch (plural){
                case true:
                    switch (rank){
                        case 0: 
                            std::cout << "As";
                            break;
                        case 10:
                            std::cout << "Js";
                            break;
                        case 11:
                            std::cout << "Qs";
                            break;
                        case 12:
                            std::cout << "Ks";
                            break;      
                        default:
                            std::cout << rank + 1 << "s";
                            break;
                    }
                    break;
                case false:
                    switch (rank){
                        case 0: 
                            std::cout << "A";
                            break;
                        case 10:
                            std::cout << "J";
                            break;
                        case 11:
                            std::cout << "Q";
                            break;
                        case 12:
                            std::cout << "K";
                            break;      
                        default:
                            std::cout << rank + 1;
                            break;
                    }
                    break;
        }
            break;
    }
}
void displayCard(int suit, int rank) {
    if (suit == -1 && rank == -1)
    {
        std::cout << "no card.\n";
        return;
    }
    else {
    displayRank(rank, true, true, false);
    switch (suit){
        case -1:
            break;
        default:
            std::cout << " of ";
            break;
    }
    displaySuit(suit, true, true);
    }
}
/// @brief selects a card at random
/// @param amount how many cards to deal 
/// @return dealt card
int dealCard(int amount) {
    if (amount >= 1 && amount < 53) {
        std::cout << "\nDealt the card: ";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);
        std::uniform_int_distribution<> dis2(0, 12);
        int suit = dis(gen);
        int rank = dis2(gen);
        displayCard(suit, rank);
        std::cout << std::endl;
        if (dealtCards[suit][rank] == 1) {
            std::cout << "\nBut that card was already dealt. Trying to deal another one.\n";
            return dealCard(amount);            
        }
        dealtCards[suit][rank] = 1;
        dealtSuit = suit;
        dealtRank = rank;
        return suit, rank, dealCard(--amount); ///check if this is correct ///yeah i think this is correct //it does work, i just don't know how.
    }
    else {
        return 0;
    }
}

void initCards() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards[i][j] = j + 1;
        }
    }
}

bool zeroFirstDesc(int a, int b){
    if (a == 0) return true;
    if (b == 0) return false;
    return a > b;
}

void setArrayToValue(int* arr, size_t size, int value){
    for (size_t i = 0; i < size; i++){
        arr[i] = value;
    }
}