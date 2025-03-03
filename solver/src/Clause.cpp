//
// Created by Emil Watz on 26.02.2025.
//

#include "../include/Clause.h"

void Clause::addVariable(long varId, bool polarity) {
    variables.emplace(varId, polarity);
}

bool Clause::removeVariable(long varId) {
    return variables.erase(varId) == 1;
}

bool Clause::isEmpty() const {
    return variables.empty();
}

std::unordered_map<long, bool>::const_iterator Clause::begin() {
    return variables.begin();
}

std::unordered_map<long, bool>::const_iterator Clause::end() {
    return variables.end();
}
