//
// Created by Emil Watz on 01.02.2025.
//

#include "include/VariableClauseRelation.h"

#include <algorithm>
#include <iostream>
#include <utility>


VariableClauseRelation::VariableClauseRelation() {
    //std::cout << "New VariableClauseRelation" << '\n';
}

long VariableClauseRelation::addClause() {
    clausesToVariableMap.emplace_back();
    return clausesToVariableMap.size() - 1;
}

long VariableClauseRelation::addVariableToClause(long clauseId, bool polarity) {
    if (clausesToVariableMap.size() > clauseId) {
        long newVarId = variableToClauseMap.size();
        Variable v(newVarId);
        v.addClause(clauseId, polarity);
        variableToClauseMap.push_back(v);
        clausesToVariableMap.at(clauseId).addVariable(newVarId, polarity);
        return newVarId;
    } else {
        throw std::runtime_error("Clause does not exist");
    }
}

void VariableClauseRelation::addVariableToClause(long clauseId, long varId, bool polarity) {
    if (variableToClauseMap.size() <= varId) {
        throw std::out_of_range("Variable Id out of range!");
    }
    if (clausesToVariableMap.size() <= clauseId) {
        throw std::out_of_range("Clause Id out of range!");
    }
    variableToClauseMap.at(varId).addClause(clauseId, polarity);
    clausesToVariableMap.at(clauseId).addVariable(varId, polarity);
}

CNFFormula VariableClauseRelation::setupFormula(std::map<long, long> fileToInternalVar, std::map<long, long> internalToFileVar) {
    //std::make_heap(variables.begin(), variables.end(), variable_comparison);
    CNFFormula c(clausesToVariableMap, variableToClauseMap, std::move(fileToInternalVar), std::move(internalToFileVar));
    return c;
}
