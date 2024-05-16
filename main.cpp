#include <iostream>
#include <random>
#include <bits/stdc++.h> 

/*  i = 0 -> spades
    i = 1 -> clubs
    i = 2 -> diamonds
    i = 3 -> hearts 
*/
int cards[4][13];               //is cards
int dealtCards[4][13];          //stores if a card is dealt or not. 0-> not dealt, 1-> dealt.
int dealtSuit;                  //stores the most recently dealt (selected at random) suit
int dealtRank;                  //stores the most recently dealt (selected at random) rank
int dealtCard[2];               //combines the two values above, idk if this is needed
bool firstRound = true;         //so we can have a gameloop i guess
const int PLAYERCOUNT = 4;      //default playercount, note that changing this does not actually add new players. this is just for displaying player count.
const int PLAYERMONEY = 1000;   //default starting money. 
const int PLAYERBET = 0;        //default starting bet.
int bustedPlayerCount = 0;      //is busted player count
int bufferSuit;                 //idk where i used this
int bufferRank;                 //same as bufferSuit


void displayCard(int suit, int rank) {
    if (suit == -1 && rank == -1)
    {
        std::cout << "No card dealt yet.\n";
        return;
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
void listCards() { //this function is completely unnecessary and the symbols cannot be displayed outside vscode just yet. //but it stays c:
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
        
    public:
        int handScore;              //may not use this.
        int pWideHand[7][2];        //= community + player cards
        int pShortHand[5][2];       //the best evaluated hand.
        int pShortHandBuffer[5][2]; //the best evaluated hand 2: electric boogaloo because i am stupid
        int heldCards[2][2];        //player cards
        int flushCards[7][2];       //we pass this to straight() after a flush so we can check for a straight flush
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
        std::cout << std::endl;
        takeBets();
        dealCommunityCards(3);
        std::cout << std::endl;
        updatePlayerHands();
        std::cout << std::endl;
        takeBets();
        dealCommunityCards(1);
        std::cout << std::endl;
        updatePlayerHands();
        std::cout << std::endl;
        takeBets();
        dealCommunityCards(1);
        std::cout << std::endl;
        updatePlayerHands();
        std::cout << std::endl;
        takeBets();
        players[0].getHeldCards(3, true);
        players[1].getHeldCards(3, true);
        players[2].getHeldCards(3, true);
        players[3].getHeldCards(3, true);
        
        
        displayCommunityCards();
        scoreHands();

    }
    void debugMode() {
        dealFirstCards();
        updatePlayerHands();
        setCommunityCards(0, 9, 2, 3, 0, 10, 0, 11, 0, 12);
        players[0].getHeldCards(3, true);
        players[1].getHeldCards(3, true);
        players[2].getHeldCards(3, true);
        players[3].getHeldCards(3, true);
        
        
        displayCommunityCards();
        scoreHands();
    }
    void setCommunityCards(int s1, int r1, int s2, int r2, int s3, int r3, int s4, int r4, int s5, int r5){
        communityCards[0][0] = s1;
        communityCards[0][1] = r1;
        updatePlayerHands();
        communityCards[1][0] = s2;
        communityCards[1][1] = r2;
        updatePlayerHands();
        communityCards[2][0] = s3;
        communityCards[2][1] = r3;
        updatePlayerHands();
        communityCards[3][0] = s4;
        communityCards[3][1] = r4;
        updatePlayerHands();
        communityCards[4][0] = s5;
        communityCards[4][1] = r5;
        updatePlayerHands();
        

    }
    void displayCommunityCards() {
        for (int i = 0; i < 5; i++) {
            std::cout << "Community card " << i + 1 << " is: ";
            displayCard(communityCards[i][0], communityCards[i][1]);
            std::cout << std::endl;
        }
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
            //std::cout << "Community card " << x + 1 << " is: ";
            //displayCard(communityCards[x][0], communityCards[x][1]);
            //std::cout << std::endl;
            //commented out to reduce output
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
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                players[i].pWideHand[j][0] = players[i].heldCards[j][0];
                players[i].pWideHand[j][1] = players[i].heldCards[j][1];
            }
        }
        for (int i = 0; i < 5; i++) {
            players[0].pWideHand[i + 2][0] = communityCards[i][0];
            players[0].pWideHand[i + 2][1] = communityCards[i][1];
            players[1].pWideHand[i + 2][0] = communityCards[i][0];
            players[1].pWideHand[i + 2][1] = communityCards[i][1];
            players[2].pWideHand[i + 2][0] = communityCards[i][0];
            players[2].pWideHand[i + 2][1] = communityCards[i][1];
            players[3].pWideHand[i + 2][0] = communityCards[i][0];
            players[3].pWideHand[i + 2][1] = communityCards[i][1];
        }

       }

    void scoreHands() {
        //TODO: implement scoring
        for (int i = 0; i < 4; i++) {
            flush(i);
        }
        for (int i = 0; i < 4; i++) {
            straight(i, false);
        }
    }
    int flush(int id) {
        std::string flushSuit = "None";
        int flushCounter = 0;
        int Fspades = 0;
        int Fclubs = 0;
        int Fdiamonds = 0;
        int Fhearts = 0;
        for (int i = 0; i < 7; i++) {
            switch (players[id].pWideHand[i][0])
            {
            case 0:
                Fspades++;
                break;
            case 1:
                Fclubs++;
                break;
            case 2:
                Fdiamonds++;
                break;
            case 3:
                Fhearts++;
                break;
            }
        }
        //choose the highest flush count
        if (Fspades >= 5){
            flushCounter = Fspades;
            flushSuit = "Spades";
        }
        else if (Fclubs >= 5){
            flushCounter = Fclubs;
            flushSuit = "Clubs";
        }
        else if (Fdiamonds >= 5){
            flushCounter = Fdiamonds;
            flushSuit = "Diamonds";
        }
        else if (Fhearts >= 5){
            flushCounter = Fhearts;
            flushSuit = "Hearts";
        }
        
        if (flushCounter >= 5) {
            std::cout << "Player " << id + 1 << " has a flush of " << flushSuit << "!\n";
            return 1;
        }
        else {
            std::cout << "Player " << id + 1 << " does not have a flush.\n";
            return 0;
        }
        bool flush = false;
        return flush;
    }
    int straight(int id, bool shortHand = false) {
        int sCounter = 1;
        bool straight = false;
        int currentStraight[5] = {-1, -1, -1, -1, -1}; 
        if (shortHand == false){        
            int ranks[7];
            for (int i = 0; i < 7; i++) {
                ranks[i] = players[id].pWideHand[i][1];
            }
            int n = sizeof(ranks) / sizeof(ranks[0]);
            std::sort(ranks, ranks + n, std::greater<int>());
            currentStraight[0] = ranks[0];
            for (int i = 0; i < 7; i++) {
                if ((currentStraight[0] == 12) && (currentStraight[1] == 11) && (currentStraight[2] == 10) && (currentStraight[3] == 9)){ //the current hand has a chance to be a broadway.
                    for (int j = i; j < 7; j++ ){
                        if (ranks[j] == 0){
                            std::cout << "Player " << id + 1 << " has a Broadway Straight!" << std::endl;
                            straight = true;
                            break;
                        }
                    }
                }
                if(straight){
                    break;
                }
                
                else if (ranks[i] - ranks[i + 1] == 1) {                            //PROBABLY REMOVE i - i+1 = 9 part is necessary for broadway hand recognition. although the problem with that is ace will be the last card on the hand. so it will most likely not be neighboring the 10. 
                    currentStraight[sCounter] = ranks[i+1];
                    sCounter++;                                                     // one solution might be to check if the ongoing straight is a K-Q-J-10. If so, we would just check for an Ace in the hand and if it returns true, the player has a broadway straight.
                    if (sCounter >= 5){                                             //check if the player just completed the straight, so we don't keep checking unnecessarily.
                        straight = true;                                            //also the next check might reset the counter. so this is necessary
                        break;
                    }
                }
                else if (ranks[i] - ranks[i + 1] == 0) {                            //the straight hasn't broken yet but didn't continue either. so we don't touch it.
                    //wtf is this shit
                    //maybe should've used a switch
                    //anyways do nothing so maybe the straight will continue
                    //TODO: commit suicide
                }
                else {
                    //reset the counter and currentStraight
                    for (int j = 0; j < 5; j++){
                        currentStraight[j] = -1;
                    }
                    sCounter = 1;
                }
            }
            if (straight){
                std::cout << "Player " << id + 1 << " has a straight!\n";
            }
            else{
                std::cout << "Player " << id + 1 << " does not have a straight.\n";
            }
        return 0;
    }
        else {
            int ranks[7];

        }
        return 0;
    }
    int duplicate(int id) {
        bool duplicate = false;
        return duplicate;
    }
    void displayHand(int id) {
        int s;
        int r;
        for (int i = 0; i < 7; i++) {    
            s = players[id].pWideHand[i][0];
            r = players[id].pWideHand[i][1];
            displayCard(s, r);
        }
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
    //game.gameLoop();
    game.debugMode();
    std::cout << "\nPress Enter to quit.";
    std::cin.get();
    return 0;
    }