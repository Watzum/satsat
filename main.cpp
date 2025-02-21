//
// Created by Emil Watz on 01.02.2025.
//

#include <fstream>
#include <iostream>
#include <string>

#include "solver/include/DimacsReader.h"
#include "solver/include/VariableClauseRelation.h"


using namespace std;

int main() {
    std::cout << "Hello World" << std::endl;
    VariableClauseRelation f;

    try {
        DimacsReader r{"../dimacsTest.dimacs", f};
        r.readFile();
    } catch (std::exception& er) {
        std::cout << er.what() << std::endl;
        return 1;
    }
    return 0;
}