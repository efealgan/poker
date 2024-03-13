#include <iostream>
#include <random>

/*  i = 0 -> spades   
    i = 1 -> clubs
    i = 2 -> diamonds
    i = 3 -> hearts 
*/
int cards[4][13];
int dealtCards[4][13];
int dealtSuit;
int dealtRank;
int dealtCard[2];
int playerCount = 1;

void displayCard(int suit, int rank) {
    if (suit == -1 && rank == -1)
    {
        std::cout << "No card dealt yet.\n";
    }
    
    if (rank == 0) {
        std::cout << "Ace of ";
    }
    else if (rank < 10) {
        std::cout << cards[suit][rank] << " of ";
    }
    else if (rank == 10) {
        std::cout << "Jack of ";
    }
    else if (rank == 11) {
        std::cout << "Queen of ";
    }
    else if (rank == 12) {
        std::cout << "King of ";
    }

    if (suit == 0) {
        std::cout << "Spades ";
    }
    else if (suit == 1) {
        std::cout << "Clubs ";
    }
    else if (suit == 2) {
        std::cout << "Diamonds ";
    }
    else if (suit == 3) {
        std::cout << "Hearts ";
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
            if (dealtCards[suit][rank] == 1) {
                std::cout << "\nBut that card was already dealt. Trying to deal another one.\n";
                return dealCard(amount);
            }
        dealtCards[suit][rank] = 1;
        dealtSuit = suit;
        dealtRank = rank;
        return suit, rank, dealCard(--amount); ///check if this is correct ///yeah i think this is correct
    }
    else {
        std::cout << "\nInvalid amount of cards to deal.\n";
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
void listCards() {
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
class Players {
        int playerID;
        int money;
        int bet;
        int heldCards[2][2] = {{-1, -1}, {-1, -1}};
        public:
        void initPlayer(int id, int m, int b) {
            playerID = id;
            money = m;
            bet = b;
            std::cout << "Player " << playerID << " has been initialized with " << 
            money << " money, " << 
            bet << " bet, and has no cards dealt yet.\n";
        }
        /// @brief heldCards setter
        /// @param x card slot; 0 -> first slot
        ///                     1 -> second slot            
        /// @param suit [0-3]
        /// @param rank [0-12]
        void setHeldCards(int x, int s, int r) {
            if (x == 1) // first card is selected
            {
                this->heldCards[0][0] = s;
                this->heldCards[0][1] = r;
                std::cout << this->playerID << " has been dealt the card "; displayCard(heldCards[0][0], heldCards[0][1]);
            }
            else if (x == 2) // second card is selected
            {
                this->heldCards[1][0] = s;
                this->heldCards[1][1] = r;
                std::cout << this->playerID << " has been dealt the card "; displayCard(heldCards[0][1], heldCards[1][1]);
            }
            else
            {
                std::cout << "Invalid card slot.\n";
            }
            
        }
        void dealToPlayer(int amount) {
            for (int i = 0; i < amount; i++) {
                if (heldCards[0][0] == -1 && heldCards[0][1] == -1) {
                    dealCard(1);
                    setHeldCards(1, dealtSuit, dealtRank);
                }
                else if (this->heldCards[1][0] == -1 && this->heldCards[1][1] == -1) {
                    dealCard(1);
                    this->setHeldCards(2, dealtSuit, dealtRank);
                }
                else {
                    std::cout << "Player " << playerID << " already has 2 cards dealt.\n";
                }
            }
        }
        
    
};
std::vector<Players> players;

void createPlayer(int id, int m, int b) {
    Players player;
    player.initPlayer(id, m, b);
    players.push_back(player);
}
void gameInit() {
    std::cout << "How many players are there? ";
    std::cin >> playerCount;
    Players player[playerCount];
    for (int i = 0; i < playerCount; i++) {
        createPlayer(i + 1, 100, 0);
    }
    for (int i = 0; i < playerCount; i++) {
        player[i].dealToPlayer(2);
    }
}





int main() {
    initCards();
    listCards();
    gameInit();
    return 0;
}