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

void printAssignment(const dimacs::varAssignment assignment[], size_t size, const std::vector<size_t>& m) {
    for (int i = 0; i < size; i++) {
        if (assignment[i] == dimacs::FALSE) {
            std::cout << "-";
        }
        if (assignment[i] != dimacs::UNKNOWN) {
            std::cout << i << " ";
        }
    }
    std::cout << '\n';
}

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


bool iterativeTrivialBranching(CNFFormula& formula, const std::vector<size_t>& internalToFileVarMapping) {
    std::stack<std::pair<size_t, dimacs::varAssignment>> variables;
    variables.push(std::make_pair<size_t, dimacs::varAssignment>(0, dimacs::varAssignment::UNKNOWN));
    variables.push(std::make_pair<size_t, dimacs::varAssignment>(0, dimacs::varAssignment::TRUE));
    variables.push(std::make_pair<size_t, dimacs::varAssignment>(0, dimacs::varAssignment::FALSE));
    dimacs::varAssignment assignment[formula.getVariableCount()];
    for (int i = 0; i < sizeof(assignment) / sizeof(dimacs::varAssignment); i++) {
        assignment[i] = dimacs::UNKNOWN;
    }
    while (!variables.empty()) {
        auto v = variables.top();
        variables.pop();
        assignment[v.first] = v.second;
        if (formula.getVariableAssignment(v.first) != dimacs::UNKNOWN) {
            formula.revokeVariableAssignment(v.first);
        }
        if (v.second == dimacs::TRUE) {
            formula.assignVariable(v.first, true);
        } else if (v.second == dimacs::FALSE) {
            formula.assignVariable(v.first, false);
        }
        if (formula.getAssignmentState() == dimacs::TRUE) {
            std::cout << "SAT ";
            printAssignment(assignment,
                sizeof(assignment) / sizeof(dimacs::varAssignment), internalToFileVarMapping);
            return true;
        }
        if (v.second != dimacs::UNKNOWN && v.first + 1 < formula.getVariableCount()) {
            variables.push(std::make_pair<size_t, dimacs::varAssignment>(v.first + 1, dimacs::varAssignment::UNKNOWN));
            variables.push(std::make_pair<size_t, dimacs::varAssignment>(v.first + 1, dimacs::varAssignment::TRUE));
            variables.push(std::make_pair<size_t, dimacs::varAssignment>(v.first + 1, dimacs::varAssignment::FALSE));
        }
    }
    return false;
}


bool dimacs::solveIterative(const std::string& filePath) {
    CNFFormula formula;

    DimacsReader reader(formula);
    std::vector<size_t> mapping = reader.readFile(filePath);
    auto start = std::chrono::system_clock::now();
    bool ret{iterativeTrivialBranching(formula, mapping)};
    std::cout << ret << std::endl;;
    auto end = std::chrono::system_clock::now();
    std::cout << end-start << std::endl;
    return ret;
}

bool dimacs::solveRecursive(const std::string& filePath) {
    CNFFormula formula;

    DimacsReader reader(formula);
    std::vector<size_t> mapping = reader.readFile(filePath);
    auto start = std::chrono::system_clock::now();
    bool ret{recursiveTrivialBranching(formula)};
    std::cout << ret << std::endl;;
    auto end = std::chrono::system_clock::now();
    std::cout << end-start << std::endl;
    return ret;
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
    while (fileReader.peek() == ' ') {
        fileReader.ignore(1);
    }
}