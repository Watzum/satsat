//
// Created by Emil Watz on 16.02.2025.
//

#ifndef DIMACS_H
#define DIMACS_H

#include <string>

#include "Variable.h"

namespace dimacs {
    void solve(const std::string&);
    long to_positive_long(const std::string&);
    void ignore_whitespaces(std::ifstream&);
    struct purity_comparison {
        bool operator()(const Variable* const a, const Variable* const b) {
            if (a->getCompareValue() < b->getCompareValue()) {
                return false;
            }
            return true;
        }
    };
}



#endif //DIMACS_H
