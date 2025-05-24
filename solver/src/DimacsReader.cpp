//
// Created by Emil Watz on 08.02.2025.
//

#include "include/DimacsReader.h"

#include <iostream>
#include <map>
#include <string>

#include "include/CNFFormula.h"
#include "include/Dimacs.h"
#include "include/DimacsFormatException.h"

DimacsReader::DimacsReader(CNFFormula& formula): relation(formula) {
}


std::vector<size_t> DimacsReader::readFile(const std::string& filePath) {
    std::vector<size_t> internalToFileVariableMapping;
    fileReader = std::ifstream{filePath};
    if (!fileReader) {
        throw std::runtime_error("Could not open dimacs file!");
    }
    readHeader();
    readClauses(internalToFileVariableMapping);
    fileReader.close();
    return internalToFileVariableMapping;
}


void DimacsReader::readHeader() {
    std::string strInput{};
    char p;
    fileReader.read(&p, 1);
    if (p != 'p') {
        throw DimacsFormatException("File does not start with 'p'");
    }

    char* buf = new char[3];
    dimacs::ignore_whitespaces(fileReader);
    fileReader.read(buf, 3);
    if (buf[0] != 'c' || buf[1] != 'n' || buf[2] != 'f') {
        throw DimacsFormatException("Expected keyword 'cnf'");
    }
    delete buf;
    fileReader >> strInput;
    long variableCount = dimacs::to_positive_long(strInput);
    fileReader >> strInput;
    long clauseCount = dimacs::to_positive_long(strInput);
    dimacs::ignore_whitespaces(fileReader);
    char linebreak;
    fileReader.get(linebreak);
    if (linebreak != '\n') {
        throw DimacsFormatException("Wrong dimacs-header format!");
    }
}

void DimacsReader::readClauses(std::vector<size_t>& mapping) {
    std::map<long, long> fileToInternal;
    std::string strInput{};
    std::string clause{};
    long long currentClause = -1;
    while (fileReader >> strInput) {
        if (currentClause == -1) {
            currentClause = relation.addNewClause();
        }
        if (strInput == "0") {
            if (currentClause == -1) {
                throw DimacsFormatException("Empty clause detected");
            }
            currentClause = -1;
        } else {
            long varFileNumber; //file number of a variable may differ from the internal id
            bool polarity;
            if (strInput.at(0) == '-') {
                varFileNumber = dimacs::to_positive_long(strInput.substr(1));
                polarity = false;
            } else {
                varFileNumber = dimacs::to_positive_long(strInput);
                polarity = true;
            }
            if (auto search = fileToInternal.find(varFileNumber); search != fileToInternal.end()) {
                relation.addVariableToClause(search->second, currentClause, polarity);
            } else {
                size_t internalVarId = relation.addNewVariable();
                mapping.push_back(varFileNumber);
                relation.addVariableToClause(internalVarId, currentClause, polarity);
                fileToInternal.emplace(varFileNumber, internalVarId);
            }
        }
    }
    if (currentClause != -1) {
        throw DimacsFormatException("Expected 0 at the end of file");
    }
}