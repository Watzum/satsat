//
// Created by Emil Watz on 01.02.2025.
//

#include <fstream>
#include <iostream>
#include <string>

#include "include/DimacsReader.h"

using namespace std;

void test1() {
    CNFFormula f;
    auto c1 = f.addNewClause();

    auto v1 = f.addNewVariable();
    auto v2 = f.addNewVariable();

    f.addVariableToClause(v1, c1, true);
    f.addVariableToClause(v2, c1, false);

    std::cout << f.assignVariable(v1, false) << std::endl;
    std::cout << f.assignVariable(v2, true) << std::endl;
}


int main() {
    test1();
}