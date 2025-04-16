//
// Created by Emil Watz on 16.02.2025.
//


#include <fstream>
#include <string>

#include "include/Dimacs.h"

#include "include/DimacsFormatException.h"
#include "include/DimacsReader.h"


namespace dimacs {
    bool branch(CNFFormula& currentFormula, std::vector<varAssignment>& assignment, size_t currentVarId, size_t varCount) {
        CNFFormula positiveBranchFormula = currentFormula;
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

        }
        return false;
    }

    void solve(const std::string& filePath) {
        CNFFormula formula;
        DimacsReader reader(formula);
        reader.readFile(filePath);
        std::vector<varAssignment> currentAssignment(formula.getVariableCount(), UNKNOWN);
        std::cout << branch(formula, currentAssignment, 0, formula.getVariableCount()) << std::endl;
    }

    //only works with non-negative integers
    long to_positive_long(const std::string& s) {
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

    void ignore_whitespaces(std::ifstream& fileReader) {
        if (fileReader.peek() == ' ') {
            fileReader.ignore(1);
        }
    }
}
