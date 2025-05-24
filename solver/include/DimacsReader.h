//
// Created by Emil Watz on 08.02.2025.
//
#ifndef DIMACSREADER_H
#define DIMACSREADER_H

#include <fstream>
#include <string>

#include "CNFFormula.h"


class DimacsReader {
    public:
        explicit DimacsReader(CNFFormula& formula);
        std::vector<size_t> readFile(const std::string &filePath);
    private:
        CNFFormula& relation;
        std::ifstream fileReader = nullptr;

        void readHeader();
        void readClauses(std::vector<size_t>&);

};



#endif //DIMACSREADER_H
