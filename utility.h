#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
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

bool isInputNotValid() {
    if (std::cin.fail()) {
        std::cin.clear();
        char ch;
        while (std::cin.get(ch) && ch != '\n');
        fflush(stdin);
        std::cin.ignore(10000, '\n');
        return true;
    }
    return false;
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

#endif