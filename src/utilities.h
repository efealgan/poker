#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <random>
#include "globals.h"

void displayCard(int suit, int rank);
int dealCard(int amount);
void initCards();
bool zeroFirstDesc(int a, int b);
void setArrayToValue(int* arr, size_t size, int value);
#endif