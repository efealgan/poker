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
bool firstRound = true;
const int PLAYERCOUNT = 4;
const int PLAYERMONEY = 1000;
const int PLAYERBET = 0;
int bustedPlayerCount = 0;


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
    else {
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
    else {
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
        std::cout << std::endl;
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
    private:
        int playerID;
        int money;
        int bet;
        int heldCards[2][2];
    public:
        Players(int id, const int m, const int b) {
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
        void setHeldCards(int x, int s, int r) {
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
                displayCard(heldCards[0][1], heldCards[1][1]);
                std::cout << std::endl;
            }
            else
            {
                std::cout << "Invalid card slot.\n";
            }
            
        }
        ///@brief returns the cards held by the player
        ///@param x card slot; 1 -> first slot 2 -> both slots  
        int getHeldCards(int x) {
            int id = this->playerID;
            if (x == 1) {
                std::cout << "Player " << id << " has the following card: ";
                displayCard(heldCards[0][0], heldCards[0][1]);
                std::cout << std::endl;
                return heldCards[0][0], heldCards[0][1];
            }
            else if (x == 2) {
                std::cout << "Player " << id << " has the following cards: ";

                displayCard(heldCards[0][0], heldCards[0][1]);
                std::cout << " and ";
                displayCard(heldCards[1][0], heldCards[1][1]);

                std::cout << std::endl;
                return heldCards[0][0], heldCards[0][1], heldCards[1][0], heldCards[1][1];
            }
            else {
                std::cout << "Invalid card slot.\n";
                return 0;
            }
        }
        void dealToPlayer(int amount) {
            for (int i = 0; i < amount; i++) {
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
                }
            }
        }
};
class Game {
private:
    int communityCards[5][2];
    int dealtCommunityCards = 0;
public:
    Players player1;
    Players player2;
    Players player3;
    Players player4;
    

    Game() : player1(1, PLAYERMONEY, PLAYERBET),
             player2(2, PLAYERMONEY, PLAYERBET),
             player3(3, PLAYERMONEY, PLAYERBET),
             player4(4, PLAYERMONEY, PLAYERBET) {
                for (int i = 0; i < 5; i++){
                    communityCards[i][0] = -1;
                    communityCards[i][1] = -1;
                }
             }

    void gameLoop() {
        std::cout << "There are " << PLAYERCOUNT - bustedPlayerCount << " players." << std::endl;
        std::cout << "Initialized players.\n";
        dealFirstCards();
        takeBets();
        dealCommunityCards(3);
        takeBets();
        dealCommunityCards(1);
        takeBets();
        dealCommunityCards(1);
        takeBets();
        scoreHands();

    }
    void dealCommunityCards(int amount) {
    for (int i = 0; i < amount; i++)
    {    
        if (communityCards[dealtCommunityCards][0] == -1 && communityCards[dealtCommunityCards][1] == -1) {
            dealCard(1);
            communityCards[dealtCommunityCards][0] = dealtSuit;
            communityCards[dealtCommunityCards][1] = dealtRank;
            std::cout << "Community card " << dealtCommunityCards + 1 << " is: ";
            displayCard(communityCards[dealtCommunityCards][0], communityCards[dealtCommunityCards][1]);                std::cout << std::endl;
            dealtCommunityCards++;
        }
        else {
            std::cout << "Community card " << dealtCommunityCards + 1 << " has already been dealt.\n";
        }
    }
    }
    int getCommunityCard(int x) {
        if (x >= 0 && x <= 4) {
            std::cout << "Community card " << x + 1 << " is: ";
            displayCard(communityCards[x][0], communityCards[x][1]);
            std::cout << std::endl;
            return communityCards[x][0], communityCards[x][1];
        }
        else {
            std::cout << "Invalid community card slot.\n";
            return 0;
        }
    }
    void takeBets() {
        //TODO: implement betting
    }
    void scoreHands() {
        //TODO: implement hand recognition
        if (true){ //royal flush

            /* code */
        }
        else if (true){ //straight flush
        
            /* code */
        }
        else if (true){ //four of a kind
        
            /* code */
        }
        else if (true){ //full house
        
            /* code */
        }
        else if (true){ //flush
        
            /* code */
        }
        else if (true){ //straight
        
            /* code */
        }
        else if (true){ //three of a kind
        
            /* code */
        }
        else if (true){ //two pair
        
            /* code */
        }
        else if (true){ //pair
        
            /* code */
        }
        else{ //high card
        
            /* code */
        }
        
        
    }
    void dealFirstCards() { //deal 2 cards to each player
        std::cout << "\nDealing one card to each player.\n";

        player1.dealToPlayer(1);
        player2.dealToPlayer(1);
        player3.dealToPlayer(1);
        player4.dealToPlayer(1);
        std::cout << std::endl;
        player1.getHeldCards(1);
        player2.getHeldCards(1);
        player3.getHeldCards(1);
        player4.getHeldCards(1);

        std::cout << "\nDealing the second cards to the players.\n";

        player1.dealToPlayer(1);
        player2.dealToPlayer(1);
        player3.dealToPlayer(1);
        player4.dealToPlayer(1);
        std::cout << std::endl;
        player1.getHeldCards(2);
        player2.getHeldCards(2);
        player3.getHeldCards(2);
        player4.getHeldCards(2);
    }
};


int main() {
    initCards();
    listCards();

    Game game;
    game.gameLoop();

    std::cout << "\nPress Enter to quit.";
    std::cin.get();
    return 0;
    }