//
// Created by Emil Watz on 21.02.2025.
//

#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <unordered_map>

#include "Variable.h"
#include "Dimacs.h"

class Variable {
public:

    Variable() : assignment(dimacs::varAssignment::TRUE), negative_occurrences(0), positive_occurrences(0) {}

    void addClause(size_t clauseId, bool polarity);
    void removeClause(size_t clauseId);
    std::unordered_map<size_t, bool>::iterator removeClause(std::unordered_map<size_t, bool>::iterator clauseId);
    void assignValue(bool value);
    void unassignValue();

    std::unordered_map<size_t,bool>::iterator begin();
    std::unordered_map<size_t,bool>::iterator end();

    [[nodiscard]] size_t getNumberOfClauses() const;
    [[nodiscard]] long getCompareValue() const;
    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] bool isPure() const;
    [[nodiscard]] bool getPolarity() const;
    dimacs::varAssignment getAssignedValue() const;

private:
    std::unordered_map<size_t, bool> clauses;
    dimacs::varAssignment assignment;
    long negative_occurrences;
    long positive_occurrences;

};

#endif //VARIABLE_H
