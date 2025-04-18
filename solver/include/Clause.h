//
// Created by Emil Watz on 26.02.2025.
//

#ifndef CLAUSE_H
#define CLAUSE_H
#include <set>
#include <unordered_map>

#include "Dimacs.h"


class Clause {
public:
    Clause() = default;
    void addVariable(size_t varId, bool polarity);
    bool removeVariable(size_t varId);
    void addVariableAssignment(size_t varId, bool value);
    void removeVariableAssignment(size_t varId, bool value); //possible improvement: value does not have to be passed
    bool isEmpty() const;
    bool isSatisfied() const;
    dimacs::varAssignment getState();
    std::unordered_map<size_t,bool>::const_iterator begin();
    std::unordered_map<size_t,bool>::const_iterator end();

private:
    std::unordered_map<size_t, bool> variables;
    std::set<size_t> satisfyingVariables;
    std::set<size_t> unsatisfyingVariables;
    std::set<size_t> unassignedVariables;
};



#endif //CLAUSE_H
