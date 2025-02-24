//
// Created by Emil Watz on 21.02.2025.
//

#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class Variable {
public:
    Variable(long i, long n, long p) : id(i), negative_occurences(n), positive_occurences(p) {}

    long id;
    long negative_occurences;
    long positive_occurences;

    [[nodiscard]] long getCompareValue() const {
        if (negative_occurences > positive_occurences) {
            return positive_occurences;
        } else {
            return negative_occurences;
        }
    }

    [[nodiscard]] std::string to_string() const {
        std::string s = "Id: ";
        s += std::to_string(id) + "; negative Occurences: ";
        s += std::to_string(negative_occurences) + "; positive Occurences";
        s += std::to_string(positive_occurences);
        return s;
    }
};

inline bool variable_comparison(const Variable& a, const Variable& b) {
    return a.getCompareValue() > b.getCompareValue();
}

#endif //VARIABLE_H
