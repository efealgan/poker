#include "globals.h"
#include "utilities.h"

int dealtCards[4][13];
int dealtSuit;                
int dealtRank;               
int dealtCard[2];                       
int cards[4][13];              

bool firstRound = true;       
int bustedPlayerCount = 0;  
int pot;
bool wantToPlay = true; 

const int PLAYERMONEY = 1000;  
const int PLAYERBET = 0;      
const int PLAYERCOUNT = 4;     

const int ROYALFLUSHSCORE = 9;
const int STRAIGHTFLUSHSCORE = 8;
const int FOUROFAKINDSCORE = 7;
const int FULLHOUSESCORE = 6;
const int FLUSHSCORE = 5;
const int STRAIGHTSCORE = 4;
const int THREEOFAKINDSCORE = 3;
const int TWOPAIRSCORE = 2;
const int PAIRSCORE = 1;
const int HIGHCARDSCORE = 0;

int royalFlushCounter = 0;

void initGlobals() {
    for (int i = 0; i < 4; i++) {
        setArrayToValue(dealtCards[i], 13, 0);
    }
    pot = 0;
}