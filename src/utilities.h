#ifndef UTILITIES_H
#define UTILITIES_H

void displayCard(int suit, int rank);
int dealCard(int amount);
void initCards();
void listCards();
bool zeroFirstDesc(int a, int b);
void setArrayToValue(int* arr, size_t size, int value);
#endif