//
// Created by Emil Watz on 08.02.2025.
//

#include "include/DimacsReader.h"
#include "include/VariableClauseRelation.h"

#include <iostream>
#include <map>
#include <string>

#include "include/Dimacs.h"
#include "include/DimacsFormatException.h"

DimacsReader::DimacsReader(VariableClauseRelation& vcr) : relation{vcr} {
};


void DimacsReader::readFile(const std::string& filePath) {
    fileReader = std::ifstream{filePath};
    if (!fileReader) {
        throw std::runtime_error("Could not open dimacs file!");
    }
    readHeader();
    readClauses();
    fileReader.close();
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
    //std::cout << "Number of variables: " << variableCount << std::endl;
    fileReader >> strInput;
    long clauseCount = dimacs::to_positive_long(strInput);
    //std::cout << "Number of clauses: " << clauseCount << std::endl;
    dimacs::ignore_whitespaces(fileReader);
    char linebreak;
    fileReader.get(linebreak);
    if (linebreak != '\n') {
        throw DimacsFormatException("Wrong dimacs-header format!");
    }
}

void DimacsReader::readClauses() {
    std::map<long, long> variable_id_map;
    std::string strInput{};
    std::string clause{};
    long currentClause = -1;
    while (fileReader >> strInput) {
        if (currentClause == -1) {
            currentClause = relation.addClause();
        }
        if (strInput == "0") {
            if (currentClause == -1) {
                throw DimacsFormatException("Empty clause detected");
            }
            currentClause = -1;
        } else {
            long var_file_number; //file number of a variable may differ from the internal id
            bool polarity;
            if (strInput.at(0) == '-') {
                var_file_number = dimacs::to_positive_long(strInput.substr(1));
                polarity = false;
            } else {
                var_file_number = dimacs::to_positive_long(strInput);
                polarity = true;
            }
            if (auto search = variable_id_map.find(var_file_number); search != variable_id_map.end()) {
                relation.addVariableToClause(currentClause, search->second, polarity);
            } else {
                long new_var_id = relation.addVariableToClause(currentClause, polarity);
                variable_id_map.emplace(var_file_number, new_var_id);
            }
        }
    }
    if (currentClause != -1) {
        throw DimacsFormatException("Expected 0 at the end of file");
    }
}