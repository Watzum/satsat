//
// Created by Emil Watz on 08.02.2025.
//
#ifndef DIMACSREADER_H
#define DIMACSREADER_H

#include <fstream>
#include <string>

#include "VariableClauseRelation.h"

class DimacsReader {
    public:
        DimacsReader(const std::string&, VariableClauseRelation&);
        void readFile();
    private:
        VariableClauseRelation& relation;
        std::ifstream fileReader;

        void readHeader();
        void readClauses();

};



#endif //DIMACSREADER_H
