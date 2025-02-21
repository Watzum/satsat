//
// Created by Emil Watz on 08.02.2025.
//

#include "include/DimacsReader.h"
#include "include/VariableClauseRelation.h"

#include <iostream>
#include <map>
#include <string>

#include "include/Dimacs.h"

DimacsReader::DimacsReader(const std::string& filePath, VariableClauseRelation& vcr) : relation{vcr}, fileReader{filePath} {
};


void DimacsReader::readFile() {
    if (!fileReader) {
        throw std::invalid_argument("Could not open dimacs file!");
    }
    readHeader();
    readClauses();
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
    long variableCount = dimacs::to_positive_long(strInput);
    std::cout << "Number of variables: " << variableCount << std::endl;
    fileReader >> strInput;
    long clauseCount = dimacs::to_positive_long(strInput);
    std::cout << "Number of clauses: " << clauseCount << std::endl;
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
                throw std::invalid_argument("Empty clause detected");
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
}