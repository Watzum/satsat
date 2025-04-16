//
// Created by Emil Watz on 16.02.2025.
//

#ifndef DIMACS_H
#define DIMACS_H

#include <string>

#include "Variable.h"

namespace dimacs {
    enum varAssignment {TRUE, FALSE, UNKNOWN};
    void solve(const std::string&);
    long to_positive_long(const std::string&);
    void ignore_whitespaces(std::ifstream&);
    struct purity_comparison {
        bool operator()(const Variable* const a, const Variable* const b) {
            return a->getCompareValue() > b->getCompareValue();
        }
    };
}



#endif //DIMACS_H
