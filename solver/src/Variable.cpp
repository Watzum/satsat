//
// Created by Emil Watz on 26.02.2025.
//

#include <string>
#include "include/Variable.h"

void Variable::addClause(long clauseId, bool polarity) {
    clauses.emplace(clauseId, polarity);
    if (polarity) {
        positive_occurrences++;
    } else {
        negative_occurrences++;
    }
}

void Variable::removeClause(long clauseId) {
    bool p = clauses.at(clauseId);
    clauses.erase(clauseId);
    if (p) {
        positive_occurrences--;
    } else {
        negative_occurrences--;
    }
}

long Variable::getInternalId() const {
    return internal_id;
}

size_t Variable::getNumberOfClauses() const {
    return clauses.size();
}

long Variable::getCompareValue() const {
    if (negative_occurrences > positive_occurrences) {
        return positive_occurrences;
    } else {
        return negative_occurrences;
    }
}

std::string Variable::to_string() const {
    std::string s = "Id: ";
    s += std::to_string(internal_id) + "; negative Occurrences: ";
    s += std::to_string(negative_occurrences) + "; positive Occurrences";
    s += std::to_string(positive_occurrences);
    return s;
}

bool Variable::isPure() const {
    return negative_occurrences == 0 || positive_occurrences == 0;
}

//precondition: isPure() == true
bool Variable::getPolarity() const {
    if (negative_occurrences == 0) {
        return true;
    }
    return false;
}