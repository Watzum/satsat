//
// Created by Emil Watz on 26.02.2025.
//

#include "../include/Clause.h"

void Clause::addVariable(size_t varId, bool polarity) {
    variables.emplace(varId, polarity);
}

bool Clause::removeVariable(size_t varId) {
    return variables.erase(varId) == 1;
}

bool Clause::isEmpty() const {
    return variables.empty() && !satisfied;
}

bool Clause::isSatisfied() const {
    return satisfied;
}

void Clause::setSatisfied() {
    satisfied = true;
}

std::unordered_map<size_t, bool>::const_iterator Clause::begin() {
    return variables.begin();
}

std::unordered_map<size_t, bool>::const_iterator Clause::end() {
    return variables.end();
}
