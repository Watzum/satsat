//
// Created by Emil Watz on 16.02.2025.
//


#include <fstream>
#include <string>
#include <iostream>

#include "Dimacs.h"


namespace dimacs {

    //only works with non-negative integers
    long to_positive_long(char const *s) {
        if (s == nullptr) {
            throw std::invalid_argument("Expected number of variables!");
        }
        int result = 0;
        while (*s) {
            if (*s < '0' || *s > '9') {
                throw std::invalid_argument("Invalid input: " + *s);
            }
            result += *s - '0';
            if (*(s+1)) {
                result *= 10;
            }
            s++;
        }
        return result;
    }
}
