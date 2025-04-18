//
// Created by Emil Watz on 26.02.2025.
//

#include "../include/Clause.h"

#include <cassert>

void Clause::addVariable(size_t varId, bool polarity) {
    variables.emplace(varId, polarity);
    unassignedVariables.emplace(varId);
}

bool Clause::removeVariable(size_t varId) {
    unassignedVariables.erase(varId);
    unsatisfyingVariables.erase(varId);
    satisfyingVariables.erase(varId);
    return variables.erase(varId) == 1;
}

void Clause::addVariableAssignment(size_t varId, bool value) {
    assert(unassignedVariables.contains(varId));
    assert(variables.contains(varId));
    unassignedVariables.erase(varId);
    if (variables.at(varId) == value) {
        satisfyingVariables.emplace(varId);
    } else {
        unsatisfyingVariables.emplace(varId);
    }
}

void Clause::removeVariableAssignment(size_t varId, bool value) {
    assert(!unassignedVariables.contains(varId));
    if (variables.at(varId) == value) {
        assert(satisfyingVariables.contains(varId));
        satisfyingVariables.erase(varId);
    } else {
        assert(unsatisfyingVariables.contains(varId));
        unsatisfyingVariables.erase(varId);
    }
    unassignedVariables.emplace(varId);
}

bool Clause::isEmpty() const {
    return satisfyingVariables.empty() && unassignedVariables.empty();
}

bool Clause::isSatisfied() const {
    return !satisfyingVariables.empty();
}

dimacs::varAssignment Clause::getState() {
    if (!satisfyingVariables.empty()) {
        return dimacs::TRUE;
    } if (!unassignedVariables.empty()) {
        return dimacs::UNKNOWN;
    }
    return dimacs::FALSE;
}

std::unordered_map<size_t, bool>::const_iterator Clause::begin() {
    return variables.begin();
}

std::unordered_map<size_t, bool>::const_iterator Clause::end() {
    return variables.end();
}
