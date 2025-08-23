//
// Created by Emil Watz on 01.02.2025.
//

#include <iostream>

#include "include/DimacsReader.h"
#include "include/Dimacs.h"

using namespace std;

void test1() {
    //dimacs::solveIterative("../dimacsTest.dimacs");

    dimacs::solveIterative("../Google_tests/dimacsFiles/extFiles/sat/uf20-01.cnf");
    //dimacs::solveIterative("../test.dimacs");
}


int main() {
    test1();
}