//
// Created by Emil Watz on 01.02.2025.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "include/DimacsFormatException.h"
#include "include/Variable.h"
#include "solver/include/DimacsReader.h"
#include "solver/include/VariableClauseRelation.h"


using namespace std;

void test1() {
    DimacsReader d;
    CNFFormula c = d.readFile("../dimacsTest.dimacs");
    c.splitOnVariable(nullptr, false);
}


int main() {
    test1();
}