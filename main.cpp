//
// Created by Emil Watz on 01.02.2025.
//

#include <fstream>
#include <iostream>
#include <string>

#include "include/Variable.h"
#include "solver/include/DimacsReader.h"
#include "solver/include/VariableClauseRelation.h"


using namespace std;

void test1() {
    CNFFormula c;
    DimacsReader d(c);
    d.readFile("../dimacsTest.dimacs");
    cout << c.isEmptyClause() << endl;
}


int main() {
    test1();
}