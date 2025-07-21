#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <limits>
#include <iomanip>
#include <fstream>

bool isNameValid(const std::string &name) {
    if (name.length() < 4 && name.length() > 64) return false;
    for (char ch : name) {
        if (!isalpha(ch)) return false;
    }
    return true;
}

bool isPinValid(const std::string &input) {
    if (input.length() != 4) return false;
    for (char ch : input) {
        if (!isalnum(ch)) return false;
    }
    return true;
}

bool isInputValid() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool isInputNotValid() {
    return !isInputValid();
}


std::string padNumber(int number, int width) {
    std::string numStr = std::to_string(number);
    while (numStr.length() < width)
        numStr = "0" + numStr;
    return numStr;
}

std::string formatID(int prefix, int serial) {
    return padNumber(prefix, 4) + "-" + padNumber(serial, 4);
}

void systemPause() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cin.get(); 
}

#endif