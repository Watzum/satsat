//
// Created by Emil Watz on 01.02.2025.
//

#include <fstream>
#include <iostream>
#include <string>

#include "include/DimacsFormatException.h"
#include "solver/include/DimacsReader.h"
#include "solver/include/VariableClauseRelation.h"


using namespace std;

int main() {
    std::cout << "Hello World" << std::endl;

    VariableClauseRelation rel;
    DimacsReader reader3{"../Google_tests/dimacsFiles/DimacsThrow2.dimacs", rel};
    try {
        reader3.readFile();
    } catch (DimacsFormatException& ex) {
        std::cout << ex.what() << std::endl;
    }
}