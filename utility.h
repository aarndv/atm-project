#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <iomanip>
#include <fstream>

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

std::string generateRefNumber() {
    const std::string refPath = "data/ref.txt";
    int oldVal, newVal;
    
    std::ifstream fin(refPath);
    if (fin.is_open()) {
        fin >> oldVal;
        fin.close();
    } else {
        oldVal = 0;
    }
    
    newVal = oldVal + 1;
    std::ofstream fout(refPath);
    if (fout.is_open()) {
        fout << newVal;
        fout.close();
    } else {
        std::cerr << "[ERROR] Could not save reference number.\n";
    }

    std::ostringstream oss;
    oss << std::setw(6) << std::setfill('0') << newVal;
    return oss.str();
}

#endif