//
// Created by Emil Watz on 01.02.2025.
//

#ifndef VARIABLECLAUSERELATION_H
#define VARIABLECLAUSERELATION_H

#include <unordered_set>
#include <vector>
#include <utility>

#include "Clause.h"
#include "CNFFormula.h"
#include "Variable.h"

class VariableClauseRelation {
    public:
        VariableClauseRelation();
        long addClause();
        long addNewVariableToClause(long clauseId, bool polarity, long fileVarId);
        void addVariableToClause(long clauseId, long varId, bool polarity);

        CNFFormula setupFormula(std::map<long, long>, std::map<long, long>);
    private:
        std::vector<Clause> clauses;
        std::vector<Variable> variables;
};



#endif //VARIABLECLAUSERELATION_H
