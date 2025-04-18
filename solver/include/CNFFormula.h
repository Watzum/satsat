//
// Created by Emil Watz on 24.02.2025.
//

#ifndef CNFFORMULA_H
#define CNFFORMULA_H
#include <algorithm>
#include <iostream>
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
    [[nodiscard]] bool isEmptySet() const;

    [[nodiscard]] size_t getVariableCount() const;
    [[nodiscard]] dimacs::varAssignment getAssignmentState() const;

    //returns false if assignment results in an empty clause <=> unsat assignment
    void assignVariable(size_t varId, bool polarity);
    void revokeVariableAssignment(size_t varId);
    void assignUnitClauses();


private:

    void changeAssignmentState(size_t clauseId, dimacs::varAssignment prevState, dimacs::varAssignment newState);

    std::vector<Clause> clauses;
    std::vector<Variable> variables;
    std::set<size_t> emptyClauses;
    std::set<size_t> satisfiedClauses;
    std::set<size_t> unknownClauses;
    std::set<size_t> unitClauses;


};



#endif //CNFFORMULA_H
