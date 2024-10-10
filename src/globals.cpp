#include "globals.h"

int dealtCards[4][13];          
int dealtSuit;                
int dealtRank;               
int dealtCard[2];             
int bufferSuit;               
int bufferRank;                
int cards[4][13];              

bool firstRound = true;       
int bustedPlayerCount = 0;   

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