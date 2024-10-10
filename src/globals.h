#ifndef GLOBALS_H
#define GLOBALS_H


/*
    i = 0 -> spades
    i = 1 -> clubs
    i = 2 -> diamonds
    i = 3 -> hearts 
*/
/*
    j = 0 -> A
    j = 1 -> 2
    j = 2 -> 3
    ..
    ...
    ..
    j = 10 -> J
    j = 11 -> Q
    j = 12 -> K
*/

extern int dealtCards[4][13];          //stores if a card is dealt or not. 0-> not dealt, 1-> dealt.
extern int dealtSuit;                  //stores the most recently dealt (selected at random) suit
extern int dealtRank;                  //stores the most recently dealt (selected at random) rank
extern int dealtCard[2];               //combines the two values above, idk if this is needed
extern bool firstRound;                //so we can have a gameloop i guess
extern int bustedPlayerCount;          //is busted player count
extern int bufferSuit;                 //idk where i used this
extern int bufferRank;                 //same as bufferSuit
extern int cards[4][13];               //is cards

//const defaults in .cpp file
extern const int PLAYERCOUNT;   //default playercount, note that changing this does not actually add new players. this is just for displaying player count.
extern const int PLAYERMONEY;   //default starting money.
extern const int PLAYERBET;     //default starting bet.

extern const int ROYALFLUSHSCORE;
extern const int STRAIGHTFLUSHSCORE;
extern const int FOUROFAKINDSCORE;
extern const int FULLHOUSESCORE;
extern const int FLUSHSCORE;
extern const int STRAIGHTSCORE;
extern const int THREEOFAKINDSCORE;
extern const int TWOPAIRSCORE;
extern const int PAIRSCORE;
extern const int HIGHCARDSCORE;
#endif