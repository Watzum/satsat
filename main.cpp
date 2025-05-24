//
// Created by Emil Watz on 01.02.2025.
//

#include <iostream>

#include "include/DimacsReader.h"
#include "include/Dimacs.h"

using namespace std;

void test1() {
    dimacs::solve("../lorecs_example_sat.dimacs");
}


int main() {
    test1();
}