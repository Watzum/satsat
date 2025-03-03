//
// Created by Emil Watz on 01.02.2025.
//

#include "include/VariableClauseRelation.h"

#include <algorithm>
#include <iostream>
#include <utility>


VariableClauseRelation::VariableClauseRelation() = default;

long VariableClauseRelation::addClause() {
    clauses.emplace_back();
    return clauses.size() - 1;
}

long VariableClauseRelation::addNewVariableToClause(long clauseId, bool polarity, long fileVarId) {
    if (clauses.size() > clauseId) {
        long newVarId = variables.size();
        Variable& v = variables.emplace_back(newVarId, fileVarId);
        v.addClause(clauseId, polarity);
        clauses.at(clauseId).addVariable(newVarId, polarity);
        return newVarId;
    } else {
        throw std::runtime_error("Clause does not exist");
    }
}

void VariableClauseRelation::addVariableToClause(long clauseId, long varId, bool polarity) {
    if (variables.size() <= varId) {
        throw std::out_of_range("Variable Id out of range!");
    }
    if (clauses.size() <= clauseId) {
        throw std::out_of_range("Clause Id out of range!");
    }
    variables.at(varId).addClause(clauseId, polarity);
    clauses.at(clauseId).addVariable(varId, polarity);
}

CNFFormula VariableClauseRelation::setupFormula(std::map<long, long> fileToInternalVar, std::map<long, long> internalToFileVar) {
    CNFFormula c(clauses, variables, std::move(fileToInternalVar), std::move(internalToFileVar));
    return c;
}
