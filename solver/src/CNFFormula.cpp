//
// Created by Emil Watz on 24.02.2025.
//

#include "../include/CNFFormula.h"

#include <iostream>
#include <stdexcept>

/*
Variable* CNFFormula::peekVariable() {
    if (splitQueue.empty()) {
        return nullptr;
    }
    return splitQueue.at(0);
}

void CNFFormula::splitOnNextVariable(bool pol) {

    Variable* v = splitQueue.at(0);
    if (v != nullptr) {
        for (auto clause : *v) {
            if (clause.second == pol) {
                clausesToVariableMap.erase(clausesToVariableMap.begin() + clause.first);
            } else {
                v->removeClause(clause.first);
            }
        }
        std::pop_heap(splitQueue.begin(), splitQueue.end(), dimacs::purity_comparison());
        splitQueue.pop_back();
    }
}*/

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
    return clauses.size() - 1;
}


void CNFFormula::removeClause(long clauseId) {
    Clause c = clauses.at(clauseId);
    for (auto it : c) {
        Variable& v = variables.at(it.first);
        v.removeClause(clauseId);
    }
    clauses.erase(clauses.begin() + clauseId);
}


bool CNFFormula::isEmptyClause() {
    return clauses.empty();
}
