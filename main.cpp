//
// Created by Emil Watz on 01.02.2025.
//

#include <fstream>
#include <iostream>
#include <string>

#include "include/DimacsReader.h"
#include "include/Dimacs.h"

using namespace std;

void test1() {
    dimacs::solve("../dimacsTest.dimacs");
}


int main() {
    test1();
}