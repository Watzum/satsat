//
// Created by Emil Watz on 24.02.2025.
//

#ifndef CNFFORMULA_H
#define CNFFORMULA_H
#include <map>
#include <utility>
#include <vector>

#include "Clause.h"
#include "Variable.h"


class CNFFormula {
public:
    CNFFormula(std::vector<Clause> a, std::vector<Variable> b, std::map<long, long> c, std::map<long, long> d) :
                clausesToVariableMap(std::move(a)), variableToClauseMap(std::move(b)),
                fileToInternalVar(std::move(c)), internalToFileVar(std::move(d)) {};

    long getFileVarOf(long internalVar) const;
    long getInternalVarOf(long fileVar) const;
    Variable* peekVariable();
    void splitOnVariable(Variable*, bool);
    //pre: varId >= 0
    Variable& getVariable(long varId);
    //pre: clauseId >= 0
    Clause& getClause(long clauseId);
    //TODO: void removeVarFromClause(long varId, long clauseId);
    void removeClause(long clauseId);

private:
    std::vector<Clause> clausesToVariableMap;
    std::vector<Variable> variableToClauseMap;
    std::map<long, long> fileToInternalVar;
    std::map<long, long> internalToFileVar;
};



#endif //CNFFORMULA_H
