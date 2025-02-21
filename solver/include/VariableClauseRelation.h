//
// Created by Emil Watz on 01.02.2025.
//

#ifndef VARIABLECLAUSERELATION_H
#define VARIABLECLAUSERELATION_H

#include <vector>
#include <utility>

class VariableClauseRelation {
    public:
        VariableClauseRelation();
        long addClause();
        long addVariableToClause(long clauseId, bool polarity);
        void addVariableToClause(long clauseId, long varId, bool polarity);
        //pre: varId >= 0
        std::vector<std::pair<long, bool>>& getClausesOfVariable(long varId);
        //pre: clauseId >= 0
        std::vector<std::pair<long, bool>>& getVariablesOfClause(long clauseId);
    private:
        std::vector<std::vector<std::pair<long, bool>>> clausesToVariableMap;
        std::vector<std::vector<std::pair<long, bool>>> variableToClauseMap;
        //std::vector<Variable> variables;
};



#endif //VARIABLECLAUSERELATION_H
