//
// Created by Emil Watz on 01.02.2025.
//

#include <fstream>
#include <iostream>
#include <string>


#include "DimacsReader.h"
#include "VariableClauseRelation.h"
#include "Dimacs.h"


using namespace std;

int main() {
    std::cout << "Hello World" << std::endl;
    VariableClauseRelation f;

    std::cout << dimacs::to_positive_long("12a3") << '\n';
    try {
        DimacsReader r{"../dimacsTest.dimacs", f};
        r.readFile();
    } catch (std::exception& er) {
        std::cout << er.what() << std::endl;
        return 1;
    }
    return 0;
    /*long c1 = f.addClause();
    long c2 = f.addClause();
    long v1 = f.addNewVariableToClause(c1, true);
    long v2 = f.addNewVariableToClause(c1, false);

    for (auto& c : f.getVariablesOfClause(c1)) {
        cout << c.first << "; " << c.second << endl;
    }*/
}