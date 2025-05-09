//
// Created by Emil Watz on 26.02.2025.
//

#include <string>
#include "include/Variable.h"

#include <cassert>
#include <iostream>

void Variable::addClause(size_t clauseId, bool polarity) {
    clauses.emplace(clauseId, polarity);
    if (polarity) {
        positive_occurrences++;
    } else {
        negative_occurrences++;
    }
}


void Variable::removeClause(size_t clauseId) {
    bool p = clauses.at(clauseId);
    clauses.erase(clauseId);
    if (p) {
        positive_occurrences--;
    } else {
        negative_occurrences--;
    }
}

std::unordered_map<size_t, bool>::iterator Variable::removeClause(std::unordered_map<size_t, bool>::iterator it) {
    bool p = clauses.at(it->first);
    if (p) {
        positive_occurrences--;
    } else {
        negative_occurrences--;
    }
    return clauses.erase(it);
}

bool Variable::getPolarityInClause(size_t clauseId) const {
    assert(clauses.contains(clauseId));
    return clauses.at(clauseId);
}

void Variable::assignValue(bool value) {
    if (value) {
        assignment = dimacs::varAssignment::TRUE;
    } else {
        assignment = dimacs::varAssignment::FALSE;
    }
}

void Variable::unassignValue() {
    assignment = dimacs::varAssignment::UNKNOWN;
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

dimacs::varAssignment Variable::getAssignedValue() const {
    return assignment;
}


std::unordered_map<size_t, bool>::iterator Variable::begin() {
    return clauses.begin();
}


std::unordered_map<size_t, bool>::iterator Variable::end() {
    return clauses.end();
}