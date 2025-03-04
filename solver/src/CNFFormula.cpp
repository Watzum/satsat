//
// Created by Emil Watz on 24.02.2025.
//

#include "../include/CNFFormula.h"

#include <iostream>
#include <stdexcept>

long CNFFormula::getFileVarOf(long internalVar) const {
    return internalToFileVar.at(internalVar);
}

long CNFFormula::getInternalVarOf(long fileVar) const {
    return fileToInternalVar.at(fileVar);
}

Variable* CNFFormula::peekVariable() {
    if (variableToClauseMap.size() != 0) {
        return &variableToClauseMap.at(0);
    }
    return nullptr;
}

void CNFFormula::splitOnVariable(Variable * var, bool pol) {
    while (!splitQueue.empty()) {
        auto p = splitQueue.at(0);
        std::ranges::pop_heap(splitQueue, dimacs::purity_comparison());
        splitQueue.pop_back();
        std::cout << "Popped: " << p->to_string() << std::endl;
        std::cout << std::endl;
    }
}

Variable& CNFFormula::getVariable(long varId) {
    if (variableToClauseMap.size() > varId) {
        return variableToClauseMap.at(varId);
    } else {
        throw std::runtime_error("Variable does not exist");
    }
}

Clause& CNFFormula::getClause(long clauseId) {
    if (clausesToVariableMap.size() > clauseId) {
        return clausesToVariableMap.at(clauseId);
    } else {
        throw std::runtime_error("Clause does not exist");
    }
}

void CNFFormula::removeClause(long clauseId) {
    Clause c = clausesToVariableMap.at(clauseId);
    for (auto it : c) {
        Variable& v = variableToClauseMap.at(it.first);
        v.removeClause(clauseId);
    }
    clausesToVariableMap.erase(clausesToVariableMap.begin() + clauseId);
}
