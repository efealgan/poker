#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "../globals.h"
#include "players.h"

class Game {
private:
    int communityCards[5][2];
    int dealtCommunityCards = 0;
    std::vector <int> flushedCards;
public:
    Players players[4];

    Game();

    void gameLoop();
    void debugMode();
    void setCommunityCards(int s1, int r1, int s2, int r2, int s3, int r3, int s4, int r4, int s5, int r5);
    void displayCommunityCards();
    void dealCommunityCards(int amount);
    int getCommunityCard(int x);
    void takeBets();
    void updatePlayerHands();
    void scoreHands();
    int flush(int id);
    int straight(int id, bool shortHand = false, std::vector <int> flushedCards = std::vector <int>());
    int duplicate(int id);
    void displayHand(int id);
    void dealFirstCards();
};

#endif










