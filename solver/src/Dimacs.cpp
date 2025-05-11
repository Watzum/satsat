//
// Created by Emil Watz on 16.02.2025.
//


#include <fstream>
#include <string>
#include <cassert>

#include "include/Dimacs.h"

#include <algorithm>
#include <chrono>
#include <stack>

#include "include/DimacsFormatException.h"
#include "include/DimacsReader.h"

int counter = 0;

bool recursiveTrivialBranching(CNFFormula& formula, size_t currentVariable = 0) {
    if (currentVariable == formula.getVariableCount()) {
        return formula.getAssignmentState() == dimacs::TRUE;
    }
    formula.assignVariable(currentVariable, true);
    if (recursiveTrivialBranching(formula, currentVariable + 1)) {
        return true;
    }
    formula.revokeVariableAssignment(currentVariable);
    formula.assignVariable(currentVariable, false);
    if (recursiveTrivialBranching(formula, currentVariable + 1)) {
        return true;
    }
    formula.revokeVariableAssignment(currentVariable);
    return false;
}

void printAssignment(const dimacs::varAssignment assignment[], size_t size) {
    for (int i = 0; i < size; i++) {
        if (assignment[i] == dimacs::FALSE) {
            std::cout << "-";
        }
        std::cout << i << " ";
    }
    std::cout << '\n';
}

bool iterativeTrivialBranching(CNFFormula& formula) {
    std::stack<std::pair<size_t, bool>> variables;
    variables.push(std::make_pair<size_t, bool>(0, false));
    variables.push(std::make_pair<size_t, bool>(0, true));
    dimacs::varAssignment assignment[formula.getVariableCount()];
    for (int i = 0; i < sizeof(assignment) / sizeof(dimacs::varAssignment); i++) {
        assignment[i] = dimacs::UNKNOWN;
    }
    while (!variables.empty()) {
        auto v = variables.top();
        variables.pop();
        formula.assignVariable(v.first, v.second);
        if (v.second) {
            assignment[v.first] = dimacs::TRUE;
        } else {
            assignment[v.first] = dimacs::FALSE;
        }
        if (formula.getAssignmentState() == dimacs::TRUE) {
            std::cout << "SAT ";
            printAssignment(assignment, sizeof(assignment) / sizeof(dimacs::varAssignment));
            return true;
        }
        if (formula.getAssignmentState() == dimacs::UNKNOWN) {
            variables.push(std::make_pair<size_t, bool>(v.first + 1, false));
            variables.push(std::make_pair<size_t, bool>(v.first + 1, true));
        } else {
            formula.revokeVariableAssignment(v.first);
            assignment[v.first] = dimacs::UNKNOWN;
        }
    }
    return false;
}

bool branch_3(CNFFormula& formula, std::vector<size_t>& mapping, std::vector<size_t>& branchedVariables) {
    assert(formula.getVariableCount() > 0);
    formula.assignUnitClauses();
    if (formula.getAssignmentState() == dimacs::TRUE) {
        std::cout << "SAT: ";
        //std::sort(mapping.begin(), mapping.end(), [](int i, int j) { return abs(i) < abs(j); });
        for (size_t i = 0; i != formula.getVariableCount(); ++i) {
            if (formula.getVariableAssignment(i) == dimacs::FALSE) {
                std::cout << "-" << mapping.at(i) << " ";
            } else if (formula.getVariableAssignment(i) == dimacs::TRUE) {
                std::cout << mapping.at(i) << " ";
            }
        }
        std::cout << '\n';
        return true;
    }
    if (formula.getAssignmentState() == dimacs::FALSE) {
        return false;
    }
    if (formula.getAssignmentState() != dimacs::FALSE && formula.everyVariableAssigned() == false) {
        size_t varId = formula.selectUnassignedVariable();
        //std::cout << "Branch " << varId << " -> TRUE " << std::endl;
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
    //std::cout << "Branch " << currentVarId << " -> TRUE " << std::endl;
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
    //std::cout << "Branch " << currentVarId << " -> NEGATIVE " << std::endl;
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
    auto start = std::chrono::system_clock::now();

    std::cout << iterativeTrivialBranching(formula) << std::endl;;
    auto end = std::chrono::system_clock::now();
    std::cout << end-start << std::endl;
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