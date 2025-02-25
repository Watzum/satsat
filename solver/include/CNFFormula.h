//
// Created by Emil Watz on 24.02.2025.
//

#ifndef CNFFORMULA_H
#define CNFFORMULA_H
#include <map>
#include <utility>
#include <vector>

#include "Variable.h"


class CNFFormula {
public:
    CNFFormula(std::vector<std::vector<std::pair<long, bool>>> a, std::vector<std::vector<std::pair<long, bool>>> b,
        std::vector<Variable> c, std::map<long, long> d, std::map<long, long> e) :
                clausesToVariableMap(std::move(a)), variableToClauseMap(std::move(b)),
                variables_heap(std::move(c)), fileToInternalVar(std::move(d)), internalToFileVar(std::move(e)) {};

    long getFileVarOf(long internalVar);
    long getInternalVarOf(long fileVar);
    //pre: varId >= 0
    std::vector<std::pair<long, bool>>& getClausesOfVariable(long varId);
    //pre: clauseId >= 0
    std::vector<std::pair<long, bool>>& getVariablesOfClause(long clauseId);
private:
    std::vector<std::vector<std::pair<long, bool>>> clausesToVariableMap;
    std::vector<std::vector<std::pair<long, bool>>> variableToClauseMap;
    std::vector<Variable> variables_heap;
    std::map<long, long> fileToInternalVar;
    std::map<long, long> internalToFileVar;
};



#endif //CNFFORMULA_H
