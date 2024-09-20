#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../globals.h"
#include "players.h"

class Game {
private:
    int communityCards[5][2];
    int dealtCommunityCards = 0;
    std::vector <int> flushedCards;
    std::vector <Players> currentPlayers;
public:

    Game(int playerCount = PLAYERCOUNT);                                                                            //game constructor

    void gameLoop();                                                                                                //very basic game loop
    void debugMode();                                                                                               //debug mode                   
    void setCommunityCards(int s1, int r1, int s2, int r2, int s3, int r3, int s4, int r4, int s5, int r5);         //set community cards for debug mode
    void displayCommunityCards();                                                                                   //display community cards                                          
    void dealCommunityCards(int amount);                                                                            //deal community cards          
    int getCommunityCard(int x);                                                                                    //returns selected community card(s)
    void takeActions();                                                                                             //take actions for each player //not implemented yet                          
    void updatePlayerHands();                                                                                       //update player hands with new community cards                             
    void scoreHands();                                                                                              //final scoring and determining a winner
    int flush(int id);                                                                                              //check for a flush
    int straight(int id, bool shortHand = false, std::vector <int> flushedCards = std::vector <int>());             //check for a straight
    int duplicate(int id);                                                                                          //check for duplicate cards(pair, two pair, etc)
    void displayHand(int id);                                                                                       //display the player's hand
    void dealFirstCards();                                                                                          //deal 2 cards to each player, one by one
    void displayPlayerData(int playerID = -1);


};

#endif










