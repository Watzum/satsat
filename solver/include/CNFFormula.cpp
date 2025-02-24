//
// Created by Emil Watz on 24.02.2025.
//

#include "CNFFormula.h"

#include <stdexcept>

long CNFFormula::getFileVarOf(long internalVar) {
    return internalToFileVar.at(internalVar);
}

long CNFFormula::getInternalVarOf(long fileVar) {
    return fileToInternalVar.at(fileVar);
}

std::vector<std::pair<long, bool>>& CNFFormula::getClausesOfVariable(long varId) {
    if (variableToClauseMap.size() > varId) {
        return variableToClauseMap.at(varId);
    } else {
        throw std::runtime_error("Variable does not exist");
    }
}

std::vector<std::pair<long, bool>>& CNFFormula::getVariablesOfClause(long clauseId) {
    if (clausesToVariableMap.size() > clauseId) {
        return clausesToVariableMap.at(clauseId);
    } else {
        throw std::runtime_error("Clause does not exist");
    }
}