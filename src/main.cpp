//
// Created by Emil Watz on 01.02.2025.
//

#include "VariableClauseRelation.h"

#include <iostream>

using namespace std;

int main() {
    std::cout << "Hello World" << std::endl;
    VariableClauseRelation f;
    long c1 = f.addClause();
    long c2 = f.addClause();
    long v1 = f.addNewVariableToClause(c1, true);
    long v2 = f.addNewVariableToClause(c1, false);

    for (auto& c : f.getVariablesOfClause(c1)) {
        cout << c.first << "; " << c.second << endl;
    }
}