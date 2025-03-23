#include "interface.h"

int inputYesNo(std::string prompt = "") {
    std::string input;
    while (true) {
        std::cout << prompt << std::endl;
        std::getline(std::cin, input);
        if (input == "y" || input == "Y" || input.empty()) {
            return 1;
        } else if (input == "n" || input == "N") {
            return 0;
        } else {
            std::cout << "Invalid input. Please enter \"y\" or \"n\"." << std::endl;
        }
    }
}

void cls() {
std::cout << '\033[2J\033[1;1H'; //this didnt work on visual studio code terminal
}