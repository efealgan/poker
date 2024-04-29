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
        int pWideHand[7][2];
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
                displayCard(heldCards[1][0], heldCards[1][1]);
                std::cout << std::endl;
            }
            else
            {
                std::cout << "Invalid card slot.\n";
            }
            
        }
        ///@brief returns the cards held by the player
        ///@param x card slot; 1 -> first slot 2 -> second slot else -> both slots  
        int getHeldCards(int selectedSlot = 0, bool display = false) {
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
        ///@brief deals a card to the player
        void dealToPlayer(int amountToDeal) {
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
};
class Game {
private:
    int communityCards[5][2];
    int dealtCommunityCards = 0;
public:
    Players players[4];

    Game() : players{ Players(1, PLAYERMONEY, PLAYERBET),
                      Players(2, PLAYERMONEY, PLAYERBET),
                      Players(3, PLAYERMONEY, PLAYERBET),
                      Players(4, PLAYERMONEY, PLAYERBET) } {
        for (int i = 0; i < 5; i++) {
            communityCards[i][0] = -1;
            communityCards[i][1] = -1;
        }
    }

    void gameLoop() {
        std::cout << "There are " << PLAYERCOUNT - bustedPlayerCount << " players." << std::endl;
        std::cout << "Initialized players.\n";
        dealFirstCards();
        updatePlayerHands();
        takeBets();
        dealCommunityCards(3);
        updatePlayerHands();
        takeBets();
        dealCommunityCards(1);
        updatePlayerHands();
        takeBets();
        dealCommunityCards(1);
        updatePlayerHands();
        takeBets();
        players[0].getHeldCards(3, true);
        players[1].getHeldCards(3, true);
        players[2].getHeldCards(3, true);
        players[3].getHeldCards(3, true);
        
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
    void updatePlayerHands() { //get the player's cards and the community cards and merge in an array
        int callCount = 0;
        if (callCount == 0) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
            players[0].pWideHand[i][j], players[0].pWideHand[i][j + 1] = players[0].getHeldCards(j + 1);
            players[1].pWideHand[i][j], players[1].pWideHand[i][j + 1] = players[1].getHeldCards(j + 1);
            players[2].pWideHand[i][j], players[2].pWideHand[i][j + 1] = players[2].getHeldCards(j + 1);
            players[3].pWideHand[i][j], players[3].pWideHand[i][j + 1] = players[3].getHeldCards(j + 1);
                } 
            }
        }
        if (callCount > 0)
        {       
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 2; j++) {
                players[0].pWideHand[i + 2][j], players[0].pWideHand[i + 2][j + 1] = getCommunityCard(i);
                players[1].pWideHand[i + 2][j], players[1].pWideHand[i + 2][j + 1] = getCommunityCard(i);
                players[2].pWideHand[i + 2][j], players[2].pWideHand[i + 2][j + 1] = getCommunityCard(i);
                players[3].pWideHand[i + 2][j], players[3].pWideHand[i + 2][j + 1] = getCommunityCard(i);
            }
        }
        callCount++;
        }
    }
    void scoreHands() {
        //TODO: implement scoring
    }
    int flush(int id) {
        bool flush = false;
        return 0;
    }
    int straight(int id) {
        bool straight = false;
        return 0;
    }
    int duplicate(int id) {
        bool duplicate = false;
        return 0;
    }
    void dealFirstCards() { //deal 2 cards to each player
        std::cout << "\nDealing one card to each player.\n";

        players[0].dealToPlayer(1);
        players[1].dealToPlayer(1);
        players[2].dealToPlayer(1);
        players[3].dealToPlayer(1);
        std::cout << std::endl;
        players[0].getHeldCards(1);
        players[1].getHeldCards(1);
        players[2].getHeldCards(1);
        players[3].getHeldCards(1);

        std::cout << "\nDealing the second cards to the players.\n";

        players[0].dealToPlayer(1);
        players[1].dealToPlayer(1);
        players[2].dealToPlayer(1);
        players[3].dealToPlayer(1);
        std::cout << std::endl;
        players[0].getHeldCards();
        players[1].getHeldCards();
        players[2].getHeldCards();
        players[3].getHeldCards();
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