#include <iostream>
#include <vector>
#include <algorithm>
    
#include "game.h"
    
    
Game::Game() : players{ Players(1, PLAYERMONEY, PLAYERBET),
                        Players(2, PLAYERMONEY, PLAYERBET),
                        Players(3, PLAYERMONEY, PLAYERBET),
                        Players(4, PLAYERMONEY, PLAYERBET) } {
    for (int i = 0; i < 5; i++) {
        communityCards[i][0] = -1;
        communityCards[i][1] = -1;
    }
}
void Game::gameLoop() {
        std::cout << "There are " << PLAYERCOUNT - bustedPlayerCount << " players." << std::endl;
        std::cout << "Initialized players.\n";
        dealFirstCards();
        updatePlayerHands();
        std::cout << std::endl;
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
        std::cout << std::endl;
        players[0].getHeldCards(3, true);
        players[1].getHeldCards(3, true);
        players[2].getHeldCards(3, true);
        players[3].getHeldCards(3, true);
        
        
        displayCommunityCards();
        scoreHands();

    }

void Game::debugMode() {
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

void Game::setCommunityCards(int s1, int r1, int s2, int r2, int s3, int r3, int s4, int r4, int s5, int r5){
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

void Game::displayCommunityCards() {
    for (int i = 0; i < 5; i++) {
        std::cout << "Community card " << i + 1 << " is: ";
        displayCard(communityCards[i][0], communityCards[i][1]);
        std::cout << std::endl;
    }
}

void Game::dealCommunityCards(int amount) {
    for (int i = 0; i < amount; i++)
    {    
        if (communityCards[dealtCommunityCards][0] == -1 && communityCards[dealtCommunityCards][1] == -1) {
            dealCard(1);
            communityCards[dealtCommunityCards][0] = dealtSuit;
            communityCards[dealtCommunityCards][1] = dealtRank;
            std::cout << "Community card " << dealtCommunityCards + 1 << " is: ";
            displayCard(communityCards[dealtCommunityCards][0], communityCards[dealtCommunityCards][1]);
            dealtCommunityCards++;
        }
        else {
            std::cout << "Community card " << dealtCommunityCards + 1 << " has already been dealt.\n";
        }
    }
}

int Game::getCommunityCard(int x) {
    if (x >= 0 && x <= 4) {
        return communityCards[x][0], communityCards[x][1];
    }
    else {
        std::cout << "Invalid community card slot selected at Game::getCommunityCard.\n";
        return 0;
    }
}

void Game::takeBets() {
    //TODO: implement betting
}
/// @brief get the player's cards and the community cards and merge in an array
void Game::updatePlayerHands() { 
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

void Game::scoreHands() {
        //TODO: implement scoring
        for (int i = 0; i < 4; i++) {
            flush(i);
        }
        for (int i = 0; i < 4; i++) {
            straight(i, false);
        }
    }

int Game::flush(int id) {
    std::string flushSuit = "None";
    int flushCounter = 0;
    int Fspades = 0;
    int Fclubs = 0;
    int Fdiamonds = 0;
    int Fhearts = 0;
    std::vector <int> spades;
    std::vector <int> clubs;
    std::vector <int> diamonds;
    std::vector <int> hearts;
    for (int i = 0; i < 7; i++) {
        switch (players[id].pWideHand[i][0])
        {
        case 0:
            Fspades++;
            spades.push_back(players[id].pWideHand[i][1]);
            break;
        case 1:
            Fclubs++;
            clubs.push_back(players[id].pWideHand[i][1]);
            break;
        case 2:
            Fdiamonds++;
            diamonds.push_back(players[id].pWideHand[i][1]);
            break;
        case 3:
            Fhearts++;
            hearts.push_back(players[id].pWideHand[i][1]);
            break;
        }
    }
    //choose the highest flush count
    
    if (Fspades >= 5){
        flushCounter = Fspades;
        flushSuit = "Spades";
        flushedCards = spades;
    }
    else if (Fclubs >= 5){
        flushCounter = Fclubs;
        flushSuit = "Clubs";
        flushedCards = clubs;
    }
    else if (Fdiamonds >= 5){
        flushCounter = Fdiamonds;
        flushSuit = "Diamonds";
        flushedCards = diamonds;
    }
    else if (Fhearts >= 5){
        flushCounter = Fhearts;
        flushSuit = "Hearts";
        flushedCards = hearts;
    }
    
    if (flushCounter >= 5) {
        std::cout << "Player " << id + 1 << " has a flush of " << flushSuit << "!\n";
        straight(id, true, flushedCards);
        return 1;
    }
    else {
        return 0;
    }
    bool flush = false;
    return flush;
}

int Game::straight(int id, bool shortHand, std::vector <int> flushedCards) {
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
                
                else if (ranks[i] - ranks[i + 1] == 1) {                             
                    currentStraight[sCounter] = ranks[i+1];
                    sCounter++;                                                     
                    if (sCounter >= 5){                                             
                        straight = true;                                            
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
        else {//this block is called when a player has flush and we want to check for straight flush or royal flush 
            bool royal = false;
            sort(flushedCards.begin(), flushedCards.end(), std::greater<int>());
            currentStraight[0] = flushedCards[0];
            for (int i = 0; i < flushedCards.size(); ++i){
                std::cout << flushedCards[i] << " ";
            }
            for (int i = 0; i < flushedCards.size(); i++) {
                if ((currentStraight[0] == 12) && (currentStraight[1] == 11) && (currentStraight[2] == 10) && (currentStraight[3] == 9)){ //the current hand has a chance to be a broadway.
                    for (int j = i-1; j < flushedCards.size(); j++ ){
                        if (flushedCards[j] == 0){
                            currentStraight[4] = 0; //this is a workaround for the ace being the last card in the hand. so we just add it to the end of the array. [9, 10, 11, 12, 0]
                            royal = true;
                            straight = true;
                            sCounter++;
                        }
                    }
                }
                if(straight){
                    break;
                }
                
                else if (flushedCards[i] - flushedCards[i + 1] == 1) {                             
                    currentStraight[sCounter] = flushedCards[i+1];
                    sCounter++;                                                     
                    if (sCounter >= 5){                                             
                        straight = true;                                            
                        break;
                    }
                }
                else if (flushedCards[i] - flushedCards[i + 1] == 0) {                            

                }
                else {
                    //reset the counter and currentStraight
                    for (int j = 0; j < 5; j++){
                        currentStraight[j] = -1;
                    }
                    sCounter = 1;
                }
            }
            if (straight && royal){
                std::cout << "Player " << id + 1 << " has a Royal Flush!" << std::endl;
            }
            else if (straight && !royal){
                std::cout << "Player " << id + 1 << " has a straight flush!\n";
            }
            else if (!straight){
                std::cout << "Player " << id + 1 << " does not have a straight flush.\n";
            }

        }
        return 0;
    }

int Game::duplicate(int id) {
        bool duplicate = false;
        return duplicate;
    }

void Game::displayHand(int id) {
        int s;
        int r;
        for (int i = 0; i < 7; i++) {    
            s = players[id].pWideHand[i][0];
            r = players[id].pWideHand[i][1];
            displayCard(s, r);
        }
        std::cout << std::endl;
    }
/// @brief deal 2 cards to each player, one by one
void Game::dealFirstCards() { 
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