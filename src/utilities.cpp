#include <iostream>
#include <random>
#include <iostream>
#include "utilities.h"
#include "globals.h"


void displayCard(int suit, int rank) {
    if (suit == -1 && rank == -1)
    {
        std::cout << "no card.\n";
        return;
    }
    
    if (rank == 0) {
        std::cout << "Ace";
    }
    else if (rank < 10) {
        std::cout << rank + 1;
    }
    else if (rank == 10) {
        std::cout << "Jack";
    }
    else if (rank == 11) {
        std::cout << "Queen";
    }
    else if (rank == 12){
        std::cout << "King";
    }

    if (suit == 0) {
        std::cout << " of Spades ";
    }
    else if (suit == 1) {
        std::cout << " of Clubs ";
    }
    else if (suit == 2) {
        std::cout << " of Diamonds ";
    }
    else if (suit == 3){
        std::cout << " of Hearts ";
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

void listCards() { //this function is completely unnecessary and the symbols cannot be displayed outside vscode just yet. //but it stays.
    for (int i = 0; i < 4; i++) {
        if (i == 0) {
            std::cout << "♠A ";
        }
        else if (i == 1) {
            std::cout << "♣A ";
        }
        else if (i == 2) {
            std::cout << "♦A ";
        }
        else if (i == 3) {
            std::cout << "♥A ";
        }
        for (int j = 1; j < 10; j++) {
            if (i == 0) {
                std::cout << "♠";
            }
            else if (i == 1) {
                std::cout << "♣";
            }
            else if (i == 2) {
                std::cout << "♦";
            }
            else if (i == 3) {
                std::cout << "♥";
            }
            std::cout << cards[i][j] << " ";
        }
        for (int j = 11; j < 14; j++) {
            if (i == 0) {
                std::cout << "♠";
            }
            else if (i == 1) {
                std::cout << "♣";
            }
            else if (i == 2) {
                std::cout << "♦";
            }
            else if (i == 3) {
                std::cout << "♥";
            }


            if (j == 11) {
                std::cout << "J ";
            }
            else if (j == 12) {
                std::cout << "Q ";
            }
            else if (j == 13) {
                std::cout << "K ";
            }
        }
        std::cout << std::endl;
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