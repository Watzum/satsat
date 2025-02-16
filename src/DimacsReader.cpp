//
// Created by Emil Watz on 08.02.2025.
//

#include "DimacsReader.h"

#include <iostream>

#include "VariableClauseRelation.h"

#include <string>

DimacsReader::DimacsReader(const std::string& filePath, VariableClauseRelation& vcr) : relation{vcr}, fileReader{filePath} {
};


void DimacsReader::readFile() {
    if (!fileReader) {
        throw std::invalid_argument("Could not open dimacs file!");
    }
    readHeader();
}


void DimacsReader::readHeader() {
    std::string strInput{};
    fileReader >> strInput;
    std::cout << "read: " + strInput << '\n';
    if (strInput != "p") {
        throw std::invalid_argument("File does not start with 'p'");
    }
    fileReader >> strInput;
    std::cout << "read: " + strInput << '\n';
    if (strInput != "cnf") {
        throw std::invalid_argument("Expected keyword 'cnf'");
    }
    fileReader >> strInput;
}


