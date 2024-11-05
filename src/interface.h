#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <limits>

/**
 * @brief Prompt the user for a yes or no input.
 * 
 * @param prompt The prompt message.
 * @return 1 if the user enters 'y' or 'Y', 0 if the user enters 'n' or 'N'.
 */
int inputYesNo(std::string prompt);

/**
 * @brief Clear the console screen.
 */
void cls();

#endif