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
        explicit DimacsReader(VariableClauseRelation&);
        void readFile(const std::string &filePath);
    private:
        VariableClauseRelation& relation;
        std::ifstream fileReader = nullptr;

        void readHeader();
        void readClauses();

};



#endif //DIMACSREADER_H
