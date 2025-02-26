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

std::pair<std::unordered_map<long, bool>::const_iterator, std::unordered_map<long, bool>::const_iterator> Clause::const_iter() {
    return std::make_pair(variables.begin(), variables.end());
}
