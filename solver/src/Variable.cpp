//
// Created by Emil Watz on 26.02.2025.
//

#include <string>
#include "include/Variable.h"

void Variable::addClause(size_t clauseId, bool polarity) {
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


size_t Variable::getNumberOfClauses() const {
    return clauses.size();
}


long Variable::getCompareValue() const {
    return std::min(positive_occurrences, negative_occurrences);
}


std::string Variable::to_string() const {
    std::string s = "negative Occurrences: ";
    s += std::to_string(negative_occurrences) + "; positive Occurrences: ";
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


std::unordered_map<long, bool>::const_iterator Variable::begin() {
    return clauses.begin();
}


std::unordered_map<long, bool>::const_iterator Variable::end() {
    return clauses.end();
}