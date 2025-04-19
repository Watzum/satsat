//
// Created by Emil Watz on 16.02.2025.
//


#include <fstream>
#include <string>

#include "include/Dimacs.h"

#include <cassert>

#include "include/DimacsFormatException.h"
#include "include/DimacsReader.h"


bool branch(CNFFormula& currentFormula, std::vector<dimacs::varAssignment>& assignment, size_t currentVarId, size_t varCount) {
    /*CNFFormula positiveBranchFormula = currentFormula;
    CNFFormula negativeBranchFormula = currentFormula;
    if (positiveBranchFormula.assignVariable(currentVarId, true)) {
        auto positiveAssignment = assignment;
        positiveAssignment[currentVarId] = TRUE;
        if (currentVarId + 1 < varCount) {
            if (branch(positiveBranchFormula, positiveAssignment, currentVarId+1, varCount)) {
                return true;
            }
        } else {
            return true;
        }
    } else if (negativeBranchFormula.assignVariable(currentVarId, false)) {
        auto negativeAssignment = assignment;
        negativeAssignment[currentVarId] = FALSE;
        if (currentVarId + 1 < varCount) {
            if (branch(negativeBranchFormula, negativeAssignment, currentVarId+1, varCount)) {
                return true;
            }
        } else {
            return true;
        }

    }*/
    return false;
}

bool branch_3(CNFFormula& formula, const std::vector<size_t>& mapping, std::vector<size_t>& branchedVariables) {
    assert(formula.getVariableCount() > 0);
    formula.assignUnitClauses();
    if (formula.getAssignmentState() == dimacs::TRUE) {
        std::cout << "SAT: ";
        for (size_t i = 0; i != formula.getVariableCount(); ++i) {
            if (formula.getVariableAssignment(i) == dimacs::FALSE) {
                std::cout << "-" << mapping.at(i) << " ";
            } else if (formula.getVariableAssignment(i) == dimacs::TRUE) {
                std::cout << mapping.at(i) << " ";
            }
        }
        return true;
    }
    if (formula.getAssignmentState() == dimacs::FALSE) {
        return false;
    }
    if (formula.getAssignmentState() != dimacs::FALSE && formula.everyVariableAssigned() == false) {
        size_t varId = formula.selectUnassignedVariable();
        std::cout << "Branch " << varId << " -> TRUE " << std::endl;
        formula.assignVariable(varId, true);
        branchedVariables.push_back(varId);
        if (branch_3(formula, mapping, branchedVariables)) {
            return true;
        }
    }
    formula.resetAssignment();
    size_t c = formula.addNewClause();
    for (size_t i : branchedVariables) {
        formula.addVariableToClause(i, c, false);
    }
    branchedVariables.clear();
    return branch_3(formula, mapping, branchedVariables);
}

bool branch_2(CNFFormula& currentFormula, size_t currentVarId, size_t varCount) {
    currentFormula.assignVariable(currentVarId, varCount);
    auto state = currentFormula.getAssignmentState();
    std::cout << "Branch " << currentVarId << " -> TRUE " << std::endl;
    if (state == dimacs::TRUE) {
        return true;
    }
    if (currentVarId + 1 < varCount) {
        if (branch_2(currentFormula, currentVarId + 1, varCount)) {
            return true;
        }
    }
    currentFormula.revokeVariableAssignment(currentVarId);
    currentFormula.assignVariable(currentVarId, false);
    state = currentFormula.getAssignmentState();
    std::cout << "Branch " << currentVarId << " -> NEGATIVE " << std::endl;
    if (state == dimacs::TRUE) {
        return true;
    }  if (state == dimacs::FALSE) {
        currentFormula.revokeVariableAssignment(currentVarId);
        return false;
    }
    if (currentVarId + 1 < varCount) {
        if (branch_2(currentFormula, currentVarId + 1, varCount)) {
            return true;
        }
    }
    return false;
}

void dimacs::solve(const std::string& filePath) {
    CNFFormula formula;
    std::vector<size_t> mapping;
    DimacsReader reader(formula, mapping);
    reader.readFile(filePath);
    std::vector<size_t> v;
    std::cout << branch_3(formula, mapping, v) << std::endl;
}

//only works with non-negative integers
long dimacs::to_positive_long(const std::string& s) {
    if (s.empty()) {
        throw DimacsFormatException("Expected number!");
    }
    int result = 0;
    int i = 0;
    while (i < s.size()) {
        if (s.at(i) < '0' || s.at(i) > '9') {
            std::string what_msg = "Invalid input: ";
            what_msg += s;
            throw DimacsFormatException(what_msg);
        }
        result += s.at(i) - '0';
        if (s.size() < i + 1) {
            result *= 10;
        }
        i++;
    }
    return stol(s);
}

void dimacs::ignore_whitespaces(std::ifstream& fileReader) {
    if (fileReader.peek() == ' ') {
        fileReader.ignore(1);
    }
}