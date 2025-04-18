//
// Created by Emil Watz on 24.02.2025.
//

#include "../include/CNFFormula.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

Variable& CNFFormula::getVariable(long varId) {
    if (variables.size() > varId) {
        return variables.at(varId);
    }
    throw std::runtime_error("Variable " + std::to_string(varId) + " does not exist");
}


size_t CNFFormula::addNewVariable() {
    variables.emplace_back();
    return variables.size() - 1;
}


void CNFFormula::addVariableToClause(size_t varId, size_t clauseId, bool polarity) {
    Variable& v = variables.at(varId);
    v.addClause(clauseId, polarity);
    Clause& c = clauses.at(clauseId);
    c.addVariable(varId, polarity);
}


void CNFFormula::removeVariableFromClause(size_t varId, size_t clauseId) {
    Variable& v = variables.at(varId);
    v.removeClause(clauseId);
    Clause& c = clauses.at(clauseId);
    c.removeVariable(varId);
}


Clause& CNFFormula::getClause(long clauseId) {
    if (clauses.size() > clauseId) {
        return clauses.at(clauseId);
    }
    throw std::runtime_error("Clause " + std::to_string(clauseId) + " does not exist");
}


size_t CNFFormula::addNewClause() {
    clauses.emplace_back();
    unknownClauses.emplace(clauses.size() - 1);
    return clauses.size() - 1;
}


void CNFFormula::removeClause(size_t clauseId) {
    //Removing clauses, changes the clauseIds
    assert(false);
    assert(clauses.size() > clauseId);
    Clause c = clauses.at(clauseId);
    for (auto it : c) {
        Variable& v = variables.at(it.first);
        v.removeClause(clauseId);
    }
    emptyClauses.erase(clauseId);
}


bool CNFFormula::isEmptySet() const {
    return emptyClauses.empty();
}



size_t CNFFormula::getVariableCount() const {
    return variables.size();
}

dimacs::varAssignment CNFFormula::getAssignmentState() const {
    if (!satisfiedClauses.empty()) {
        return dimacs::TRUE;
    } if (!unknownClauses.empty()) {
        return dimacs::UNKNOWN;
    }
    return dimacs::FALSE;
}

void CNFFormula::assignVariable(size_t varId, bool polarity) {
    Variable& v = variables.at(varId);
    v.assignValue(polarity);
    for (auto & it : v) {
        auto clauseId = it.first;
        Clause& c = clauses.at(clauseId);
        auto prevState = c.getState();
        c.addVariableAssignment(varId, polarity);
        auto newState = c.getState();
        changeAssignmentState(clauseId, prevState, newState);
    }
}

void CNFFormula::revokeVariableAssignment(size_t varId) {
    Variable& v = variables.at(varId);
    bool prevAssignment = v.getAssignedValue() == dimacs::TRUE ? true : false;
    for (auto& it : v) {
        auto clauseId = it.first;
        Clause& c = clauses.at(clauseId);
        auto prevState = c.getState();
        c.removeVariableAssignment(varId, prevAssignment);
        auto newState = c.getState();
        changeAssignmentState(clauseId, prevState, newState);
    }
}

void CNFFormula::changeAssignmentState(size_t clauseId, dimacs::varAssignment prevState,
    dimacs::varAssignment newState) {
    if (prevState != newState) {
        if (newState == dimacs::TRUE) {
            satisfiedClauses.emplace(clauseId);
        } else if (newState == dimacs::FALSE) {
            emptyClauses.emplace(clauseId);
        } else {
            unknownClauses.emplace(clauseId);
        }
        if (prevState == dimacs::TRUE) {
            satisfiedClauses.erase(clauseId);
        } else if (prevState == dimacs::FALSE) {
            emptyClauses.erase(clauseId);
        } else {
            unknownClauses.erase(clauseId);
        }
    }
}
