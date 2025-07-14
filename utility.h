#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <iomanip>

bool input_validation() {
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