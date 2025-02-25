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
        if (polarity) {
            variables.emplace_back(newVarId, 0, 1);
        } else {
            variables.emplace_back(newVarId, 1, 0);
        }
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
    if (polarity) {
        variables.at(varId).positive_occurences++;
    } else {
        variables.at(varId).negative_occurences++;
    }
}

CNFFormula VariableClauseRelation::setupFormula(std::map<long, long> fileToInternalVar, std::map<long, long> internalToFileVar) {
    std::make_heap(variables.begin(), variables.end(), variable_comparison);
    CNFFormula c(clausesToVariableMap, variableToClauseMap, variables, std::move(fileToInternalVar), std::move(internalToFileVar));
    return c;
}
