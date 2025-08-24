//
// Created by Emil Watz on 24.02.2025.
//

#include "../include/CNFFormula.h"

#include <cassert>
#include <iostream>
#include <stack>
#include <stdexcept>

bool CNFFormula::solveWithTrivialIterativeBranching() {
    std::stack<std::pair<size_t, dimacs::varAssignment>> variable_stack;
    if (getVariableCount() > 0) {
        variable_stack.push(std::make_pair<size_t, dimacs::varAssignment>(0, dimacs::varAssignment::UNKNOWN));
        variable_stack.push(std::make_pair<size_t, dimacs::varAssignment>(0, dimacs::varAssignment::TRUE));
        variable_stack.push(std::make_pair<size_t, dimacs::varAssignment>(0, dimacs::varAssignment::FALSE));
    }
    while (!variable_stack.empty()) {
        auto v = variable_stack.top();
        variable_stack.pop();
        if (getVariableAssignment(v.first) != dimacs::UNKNOWN) {
            revokeVariableAssignment(v.first);
        }
        if (v.second == dimacs::TRUE) {
            assignVariable(v.first, true);
        } else if (v.second == dimacs::FALSE) {
            assignVariable(v.first, false);
        }
        if (getAssignmentState() == dimacs::TRUE) {
            std::cout << "SAT ";
            //printCurrentAssignment();
            return true;
        }
        if (v.second != dimacs::UNKNOWN && v.first + 1 < getVariableCount()) {
            variable_stack.push(std::make_pair<size_t, dimacs::varAssignment>(v.first + 1, dimacs::varAssignment::UNKNOWN));
            variable_stack.push(std::make_pair<size_t, dimacs::varAssignment>(v.first + 1, dimacs::varAssignment::TRUE));
            variable_stack.push(std::make_pair<size_t, dimacs::varAssignment>(v.first + 1, dimacs::varAssignment::FALSE));
        }
    }
    return false;
}

bool CNFFormula::solveWithTrivialRecursiveBranching(size_t currentVariable) {
    if (currentVariable == getVariableCount()) {
        return getAssignmentState() == dimacs::TRUE;
    }
    assignVariable(currentVariable, true);
    if (solveWithTrivialRecursiveBranching(currentVariable + 1)) {
        return true;
    }
    revokeVariableAssignment(currentVariable);
    assignVariable(currentVariable, false);
    if (solveWithTrivialRecursiveBranching(currentVariable + 1)) {
        return true;
    }
    revokeVariableAssignment(currentVariable);
    return false;
}

bool CNFFormula::solveWithUnitPropagation() {
    assignUnitClauses();
    //Stores, which variables decided the unit propagation assignment of which variables
    std::stack<std::pair<std::size_t, dimacs::varAssignment>> assignmentStack;
    if (!unassignedVariables.empty()) {
        std::unordered_map<std::size_t, std::vector<size_t>> backtrackMap;
        auto firstVar = selectUnassignedVariable();
        assignmentStack.push(std::make_pair<>(firstVar, dimacs::TRUE));
        assignmentStack.push(std::make_pair<>(firstVar, dimacs::UNKNOWN));
        assignmentStack.push(std::make_pair<>(firstVar, dimacs::FALSE));
        while (!assignmentStack.empty()) {
            auto [variableID, assignmentValue] = assignmentStack.top();
            assignmentStack.pop();
            if (assignmentValue == dimacs::UNKNOWN) {
                auto propagatedVariables = backtrackMap.at(variableID);
                for (auto x : propagatedVariables) {
                    revokeVariableAssignment(x);
                }
                backtrackMap.erase(variableID);
                revokeVariableAssignment(variableID);
            } else {
                assignVariable(variableID, assignmentValue);
                backtrackMap.emplace(variableID, assignUnitClauses());
                if (getAssignmentState() == dimacs::TRUE) {
                    //printCurrentAssignment();
                    return true;
                }
                if (getAssignmentState() == dimacs::UNKNOWN) {
                    auto nextVar = selectUnassignedVariable();
                    assignmentStack.push(std::make_pair<>(nextVar, dimacs::UNKNOWN));
                    assignmentStack.push(std::make_pair<>(nextVar, dimacs::TRUE));
                    assignmentStack.push(std::make_pair<>(nextVar, dimacs::UNKNOWN));
                    assignmentStack.push(std::make_pair<>(nextVar, dimacs::FALSE));
                }
            }

        }
    } else {
        return getAssignmentState() == dimacs::TRUE;
    }
    return false;
}


Variable& CNFFormula::getVariable(long varId) {
    if (variables.size() > varId) {
        return variables.at(varId);
    }
    throw std::runtime_error("Variable " + std::to_string(varId) + " does not exist");
}

dimacs::varAssignment CNFFormula::getVariableAssignment(size_t varId) const {
    assert(varId < variables.size());
    return variables.at(varId).getAssignedValue();
}


size_t CNFFormula::addNewVariable() {
    variables.emplace_back();
    unassignedVariables.emplace(variables.size() - 1);
    return variables.size() - 1;
}


void CNFFormula::addVariableToClause(size_t varId, size_t clauseId, bool polarity) {

    Variable& v = variables.at(varId);
    v.addClause(clauseId, polarity);
    Clause& c = clauses.at(clauseId);
    c.addVariable(varId, polarity);
    if (c.getNumberOfVariables() == 1) {
        unitClauses.emplace(clauseId);
        emptyClauses.erase(clauseId);
        unknownClauses.emplace(clauseId);
    } else if (c.getNumberOfVariables() == 2) {
        unitClauses.erase(clauseId);
    }
}


void CNFFormula::removeVariableFromClause(size_t varId, size_t clauseId) {
    Variable& v = variables.at(varId);
    v.removeClause(clauseId);
    Clause& c = clauses.at(clauseId);
    c.removeVariable(varId);
}


Clause& CNFFormula::getClause(long clauseId) {
    if (clauses.size() > clauseId) {
        return clauses.at(clauseId);
    }
    throw std::runtime_error("Clause " + std::to_string(clauseId) + " does not exist");
}


size_t CNFFormula::addNewClause() {
    clauses.emplace_back();
    emptyClauses.emplace(clauses.size() - 1);
    return clauses.size() - 1;
}


void CNFFormula::removeClause(size_t clauseId) {
    //Removing clauses, changes the clauseIds
    assert(false);
    assert(clauses.size() > clauseId);
    Clause c = clauses.at(clauseId);
    for (auto it : c) {
        Variable& v = variables.at(it.first);
        v.removeClause(clauseId);
    }
    emptyClauses.erase(clauseId);
}


bool CNFFormula::isEmptySet() const {
    return emptyClauses.empty();
}



size_t CNFFormula::getVariableCount() const {
    return variables.size();
}

dimacs::varAssignment CNFFormula::getAssignmentState() const {
    if (!emptyClauses.empty()) {
        return dimacs::FALSE;
    } if (!unknownClauses.empty()) {
        return dimacs::UNKNOWN;
    }
    return dimacs::TRUE;
}

void CNFFormula::assignVariable(size_t varId, bool polarity) {
    assert(unassignedVariables.contains(varId));
    Variable& v = variables.at(varId);
    v.assignValue(polarity);
    unassignedVariables.erase(varId);
    for (auto& it : v) {
        auto clauseId = it.first;
        Clause& c = clauses.at(clauseId);
        auto prevState = c.getState();
        c.addVariableAssignment(varId, polarity);
        auto newState = c.getState();
        changeAssignmentState(clauseId, prevState, newState);
        if (unitClauses.contains(clauseId) && !c.isUnitClause()) {
            unitClauses.erase(clauseId);
        } else if (c.isUnitClause()) {
            unitClauses.emplace(clauseId);
        }
    }
}

void CNFFormula::revokeVariableAssignment(size_t varId) {
    assert(!unassignedVariables.contains(varId));
    Variable& v = variables.at(varId);
    bool prevAssignment = v.getAssignedValue() == dimacs::TRUE ? true : false;
    for (auto& it : v) {
        auto clauseId = it.first;
        Clause& c = clauses.at(clauseId);
        auto prevState = c.getState();
        c.removeVariableAssignment(varId, prevAssignment);
        auto newState = c.getState();
        changeAssignmentState(clauseId, prevState, newState);
        if (unitClauses.contains(clauseId) && !c.isUnitClause()) {
            unitClauses.erase(clauseId);
        } else if (c.isUnitClause()) {
            unitClauses.emplace(clauseId);
        }
    }
    v.unassignValue();
    unassignedVariables.emplace(varId);
}

std::vector<size_t> CNFFormula::assignUnitClauses() {
    std::vector<std::size_t> assignedClauses;
    while (!unitClauses.empty()) {
        size_t unitClauseId = *unitClauses.begin();
        Clause& c = clauses.at(unitClauseId);
        auto v = c.getUnitClauseVar();
        assignVariable(v.first, v.second);
        assignedClauses.push_back(v.first);
    }
    return assignedClauses;
}

void CNFFormula::resetAssignment() {
    for (size_t v = 0; v != variables.size(); ++v) {
        if (!unassignedVariables.contains(v)) {
            revokeVariableAssignment(v);
        }
    }
}

size_t CNFFormula::selectUnassignedVariable() const {
    assert(!unassignedVariables.empty());
    return *unassignedVariables.begin();
}

bool CNFFormula::everyVariableAssigned() const {
    return unassignedVariables.empty();
}

void CNFFormula::printCurrentAssignment() const {
    for (size_t i = 0; i != variables.size(); ++i) {
        std::cout << "Var " << i << " -> ";
        if (variables.at(i).getAssignedValue() == dimacs::UNKNOWN) {
            std::cout << "UNASSIGNED";
        } else if (variables.at(i).getAssignedValue() == dimacs::TRUE) {
            std::cout << "TRUE";
        } else {
            std::cout << "FALSE";
        }
        std::cout << '\n';
    }
}

void CNFFormula::changeAssignmentState(size_t clauseId, dimacs::varAssignment prevState,
                                       dimacs::varAssignment newState) {
    if (prevState != newState) {
        if (newState == dimacs::TRUE) {
            satisfiedClauses.insert(clauseId);
        } else if (newState == dimacs::FALSE) {
            emptyClauses.insert(clauseId);
        } else {
            unknownClauses.insert(clauseId);
        }
        if (prevState == dimacs::TRUE) {
            satisfiedClauses.erase(clauseId);
        } else if (prevState == dimacs::FALSE) {
            emptyClauses.erase(clauseId);
        } else {
            unknownClauses.erase(clauseId);
        }
    }
}
