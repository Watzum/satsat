//
// Created by Emil Watz on 24.02.2025.
//

#ifndef CNFFORMULA_H
#define CNFFORMULA_H
#include <algorithm>
#include <map>
#include <iostream>
#include <utility>
#include <vector>

#include "Clause.h"
#include "Dimacs.h"
#include "Variable.h"


class CNFFormula {
public:

    CNFFormula() = default;
    CNFFormula(const CNFFormula& c) = default;

    //Variable* peekVariable();
    //void splitOnNextVariable(bool polarity);


    //pre: varId >= 0
    Variable& getVariable(long varId);
    size_t addNewVariable();
    void addVariableToClause(size_t varId, size_t clauseId, bool polarity);
    void removeVariableFromClause(size_t varId, size_t clauseId);

    //pre: clauseId >= 0
    Clause& getClause(long clauseId);
    //TODO: void removeVarFromClause(long varId, long clauseId);
    size_t addNewClause();
    void removeClause(size_t clauseId);
    bool isEmptySet();

    size_t getVariableCount();

    //returns false if assignment results in empty clause <=> unsat assignment
    bool assignVariable(size_t varId, bool polarity);


private:
    std::vector<Clause> clauses;
    std::vector<Variable> variables;
    //std::vector<Variable*> splitQueue;
};



#endif //CNFFORMULA_H
