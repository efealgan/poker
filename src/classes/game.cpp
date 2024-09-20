#include <iostream>
#include <vector>
#include <algorithm>    //for std::sort
    
#include "game.h"
#include "../globals.h" //importing for default values of player money and bet

/// @brief game constructor, initializes 4 players and community cards //maybe this should allow for custom player count using a parameter
Game::Game(int playerCount) { 
    for (int i = 0; i < PLAYERCOUNT; i++) {
        currentPlayers.emplace_back(Players(i, PLAYERMONEY, PLAYERBET));
    }
    for (int i = 0; i < 5; i++) {
        communityCards[i][0] = -1;
        communityCards[i][1] = -1;
    }
}
/// @brief the main game loop, this is where the game is played
void Game::gameLoop() {
        std::cout << "There are " << PLAYERCOUNT - bustedPlayerCount << " players." << std::endl;
        std::cout << "Initialized players.\n";
        dealFirstCards();
        updatePlayerHands();
        std::cout << std::endl;
        takeActions();
        dealCommunityCards(3);
        updatePlayerHands();
        takeActions();
        dealCommunityCards(1);
        updatePlayerHands();
        takeActions();
        dealCommunityCards(1);
        updatePlayerHands();
        takeActions();
        std::cout << std::endl;
        players[0].getHeldCards(3, true);
        players[1].getHeldCards(3, true);
        players[2].getHeldCards(3, true);
        players[3].getHeldCards(3, true);
        
        
        displayCommunityCards();
        scoreHands();
        //TODO: game loop should actually be a loop, not just a sequence of events

    }
/// @brief a manual debug mode for testing purposes. this is not the final debug mode.
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
/// @brief used to set the community cards for debug mode, input is in the form of suit and rank. also updates player hands automatically
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
/// @brief displays the community cards
void Game::displayCommunityCards() {
    for (int i = 0; i < 5; i++) {
        std::cout << "Community card " << i + 1 << " is: ";
        displayCard(communityCards[i][0], communityCards[i][1]);
        std::cout << std::endl;
    }
}
/// @brief deals the selected amount of community cards
/// @param amount amount of community cards to deal
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
/// @brief reads the community card at the selected slot
/// @param x (0-4) selects a slot to read
/// @return returns the suit and rank of the selected community card
int Game::getCommunityCard(int x) {
    if (x >= 0 && x <= 4) {
        return communityCards[x][0], communityCards[x][1];
    }
    else {
        std::cout << "Invalid community card slot selected at Game::getCommunityCard.\n";
        return 0;
    }
}
/// @brief not implemented yet, this is where the players will take their actions like betting, folding, etc.
void Game::takeActions() {
    //TODO: implement betting
}
/// @brief get the players' cards and the community cards and merge in an array for each player. this is used to check for flushes and straights etc.
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
/// @brief not implemented fully yet. but this is where the final scoring will be done. also the order of the functions called here is important because some functions rely on others. also poker hands are checked in a specific order.
void Game::scoreHands() {
        //TODO: implement scoring
        for (int i = 0; i < 4; i++) {
            flush(i);
        }
        for (int i = 0; i < 4; i++) {
            straight(i, false);
        }
    }
/// @brief checks for all the flush related things in the player's hand
/// @param id player to check
/// @return deciding what to return here was hard so i'm just procrastinating
int Game::flush(int id) {
    std::string flushSuit = "None";
    //i think flushCounter may not be needed
    int flushCounter = 0;
    //flush counters for each suit //this can also be done by checking the size of the vectors. idk which is better performance wise.
    int Fspades = 0;
    int Fclubs = 0;
    int Fdiamonds = 0;
    int Fhearts = 0;

    //all the vectors are used to store the ranks of the cards of the same suit.
    std::vector <int> spades;
    std::vector <int> clubs;
    std::vector <int> diamonds;
    std::vector <int> hearts;
    for (int i = 0; i < 7; i++) {                                   //checks for a cards suit and adds the RANK to the corresponding vector.
        switch (players[id].pWideHand[i][0])                        //this vector is later passed to straight() to check for a straight (or royal) flush by checking the ranks.
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
    
    if (Fspades >= 5){                                              //checks for a flush and sets the flushSuit and flushCounter accordingly.
        flushCounter = Fspades;
        flushSuit = "Spades";
        flushedCards = spades;                                      //this is a workaround for the straight() function. we pass the vector of ranks of the flushed suit to check for a straight flush.
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
    
    if (flushCounter >= 5) {                                        //if the flushCounter is 5 or more, the player has a flush.
        std::cout << "Player " << id + 1 << " has a flush of " << flushSuit << "!\n";
        straight(id, true, flushedCards);                           //we call straight() with the flushedCards vector to check for a straight flush.
        return 1;
    }
    else {
        return 0;
    }
    bool flush = false;
    return flush;
}
/// @brief Checks for all the straight based things
/// @param id player to check
/// @param shortHand if the player has a flush and we want to check for straight or royal flush
/// @param flushedCards this is only used when shortHand is true, it is the vector of ranks of the flushed suit
/// @return for now returns 0, in future this will return the rank of the highest card in the straight (broadway will be 13 i guess)
int Game::straight(int id, bool shortHand, std::vector <int> flushedCards) {
        int sCounter = 1;                                                       //counter for the straight is initialized to 1 because the first card is already in the array.
        bool straight = false;                                                  //straight is set to false by default.
        int currentStraight[5] = {-1, -1, -1, -1, -1};                          //currentStraight is an array of 5 integers. it is used to check for a straight. it is initialized to -1. //TODO: maybe use a vector instead of an array
        if (shortHand == false){                                                //this block is called only to check for a straight.   
            int ranks[7];                                                       //ranks is an array of 7 integers. it is used to store the ranks of the player's hand.
            for (int i = 0; i < 7; i++) {
                ranks[i] = players[id].pWideHand[i][1];
            }
            int n = sizeof(ranks) / sizeof(ranks[0]);
            std::sort(ranks, ranks + n, std::greater<int>());                   //ranks is sorted in descending order.
            currentStraight[0] = ranks[0];
            for (int i = 0; i < 7; i++) {
                if ((currentStraight[0] == 12) && (currentStraight[1] == 11) && (currentStraight[2] == 10) && (currentStraight[3] == 9)){ //checks if the current hand has a chance to be a broadway.
                    for (int j = i; j < 7; j++ ){
                        if (ranks[j] == 0){
                            std::cout << "Player " << id + 1 << " has a Broadway Straight!" << std::endl;
                            straight = true;
                            break;
                        }
                    }
                }
                if(straight){                                                   //if the player has a broadway, we break the loop. not sure if needed tho.
                    break;
                }
                
                else if (ranks[i] - ranks[i + 1] == 1) {                        //typical straight check.     
                    currentStraight[sCounter] = ranks[i+1];
                    sCounter++;                                                     
                    if (sCounter >= 5){                                             
                        straight = true;                                            
                        break;
                    }
                }
                else if (ranks[i] - ranks[i + 1] == 0) {                        //the straight hasn't broken yet but didn't continue either. so we don't touch it.
                    //wtf is this shit
                    //maybe should've used a switch
                    //anyways do nothing so maybe the straight will continue
                    //TODO: commit suicide
                }
                else {                                                          //the straight is broken
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
        else {//this block is called when a player already has flush and we want to check for straight or royal flush //most of this is documented in the if statement above
            bool royal = false;
            sort(flushedCards.begin(), flushedCards.end(), std::greater<int>());
            currentStraight[0] = flushedCards[0];
            for (int i = 0; i < flushedCards.size(); ++i){
                std::cout << flushedCards[i] << " ";
            }
            for (int i = 0; i < flushedCards.size(); i++) {
                if ((currentStraight[0] == 12) && (currentStraight[1] == 11) && (currentStraight[2] == 10) && (currentStraight[3] == 9)){
                    for (int j = i-1; j < flushedCards.size(); j++ ){
                        if (flushedCards[j] == 0){
                            currentStraight[4] = 0; //this is a workaround for the ace being the last card in the hand. so we just add it to the end of the array. [9, 10, 11, 12, 0] // isn't it [12, 11, 10, 9, 0]?
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
/// @brief not implemented yet
/// @param id not implemented yet
/// @return not implemented yet
int Game::duplicate(int id) {
        bool duplicate = false;
        return duplicate;
    }
/// @brief uses displayCard() to display the player's hand including the community cards
/// @param id player to display
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
        for (auto&  player : currentPlayers) {
            player.dealToPlayer(1);
        }
        std::cout << std::endl;
        for (auto&  player : currentPlayers) {
            player.getHeldCards(1, true);
        }
        for (auto&  player : currentPlayers) {
            player.dealToPlayer(1);
        }
        std::cout << std::endl;
        for (auto&  player : currentPlayers) {
            player.getHeldCards(2, true);
        }
    }
    ///@brief displays the player's data
    void Game::displayPlayerData(int playerID) {
        for (const auto& player : currentPlayers) {
            if (player.getPlayerID() == playerID){
                    std::cout  << "Player ID:" << player.getPlayerID() << std::endl;
            }
        }
    std::cout << "Player ID not found.\n";
    }














