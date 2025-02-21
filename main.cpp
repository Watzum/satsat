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

void d_r() {
    std::cout << "Hello World" << std::endl;

    VariableClauseRelation rel;
    DimacsReader reader3{rel};
    try {
        reader3.readFile("../dimacsTest.dimacs");
    } catch (DimacsFormatException& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
}


void variabletest() {
    Variable v1{1, 10, 15};
    Variable v2{2, 7, 30};
    Variable v3{2, 7, 30};

    std::vector<Variable> v;
    v.emplace_back(1, 10, 15);
    v.emplace_back(2, 7, 30);
    v.emplace_back(3, 0, 2);
    v.emplace_back(4, 20, 40);
    v.emplace_back(5, 100, 100);

    for (auto i : v) {
        std::cout << i.id << std::endl;
    }

    ranges::sort(v, variable_comparison);

    std::cout << std::endl;

    for (auto i : v) {
        std::cout << i.id << std::endl;
    }
}


int main() {
    variabletest();
}