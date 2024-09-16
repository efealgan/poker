#include "globals.h"


/*
    i = 0 -> spades
    i = 1 -> clubs
    i = 2 -> diamonds
    i = 3 -> hearts 
*/

//card related
int dealtCards[4][13];          //stores if a card is dealt or not. 0-> not dealt, 1-> dealt.
int dealtSuit;                  //stores the most recently dealt (selected at random) suit
int dealtRank;                  //stores the most recently dealt (selected at random) rank
int dealtCard[2];               //combines the two values above, idk if this is needed
int bufferSuit;                 //idk where i used this
int bufferRank;                 //same as bufferSuit
int cards[4][13];               //is cards

//game related
bool firstRound = true;         //so we can have a gameloop i guess
int bustedPlayerCount = 0;      //is busted player count


//defaults
const int PLAYERMONEY = 1000;   //default starting money. 
const int PLAYERBET = 0;        //default starting bet.
const int PLAYERCOUNT = 4;      //default playercount, note that changing this does not actually add new players. this is just for displaying player count.