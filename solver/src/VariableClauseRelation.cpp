//
// Created by Emil Watz on 01.02.2025.
//

#include "include/VariableClauseRelation.h"

#include <iostream>


VariableClauseRelation::VariableClauseRelation() {
    //std::cout << "New VariableClauseRelation" << '\n';
}

long VariableClauseRelation::addClause() {
    std::vector<std::pair<long, bool>> v;
    clausesToVariableMap.push_back(v);
    return clausesToVariableMap.size() - 1;
}

long VariableClauseRelation::addVariableToClause(long clauseId, bool polarity) {
    std::vector<std::pair<long, bool>> v;
    if (clausesToVariableMap.size() > clauseId) {
        long newVarId = variableToClauseMap.size();
        v.emplace_back(clauseId, polarity);
        variableToClauseMap.push_back(v);
        clausesToVariableMap.at(clauseId).emplace_back(newVarId, polarity);
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
    variableToClauseMap.at(varId).emplace_back(clauseId, polarity);
    clausesToVariableMap.at(clauseId).emplace_back(varId, polarity);
}

std::vector<std::pair<long, bool>>& VariableClauseRelation::getClausesOfVariable(long varId) {
    if (variableToClauseMap.size() > varId) {
        return variableToClauseMap.at(varId);
    } else {
        throw std::runtime_error("Variable does not exist");
    }
}

std::vector<std::pair<long, bool>>& VariableClauseRelation::getVariablesOfClause(long clauseId) {
    if (clausesToVariableMap.size() > clauseId) {
        return clausesToVariableMap.at(clauseId);
    } else {
        throw std::runtime_error("Clause does not exist");
    }
}
