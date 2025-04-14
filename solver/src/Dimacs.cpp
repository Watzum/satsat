//
// Created by Emil Watz on 16.02.2025.
//


#include <fstream>
#include <string>

#include "include/Dimacs.h"

#include "include/DimacsFormatException.h"
#include "include/DimacsReader.h"


namespace dimacs {
    void solve(const std::string& filePath) {
        //TODO
    }

    //only works with non-negative integers
    long to_positive_long(const std::string& s) {
        if (s.empty()) {
            throw DimacsFormatException("Expected number!");
        }
        int result = 0;
        int i = 0;
        while (i < s.size()) {
            if (s.at(i) < '0' || s.at(i) > '9') {
                std::string what_msg = "Invalid input: ";
                what_msg += s;
                throw DimacsFormatException(what_msg);
            }
            result += s.at(i) - '0';
            if (s.size() < i + 1) {
                result *= 10;
            }
            i++;
        }
        return stol(s);
    }

    void ignore_whitespaces(std::ifstream& fileReader) {
        if (fileReader.peek() == ' ') {
            fileReader.ignore(1);
        }
    }
}
