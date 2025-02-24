//
// Created by Emil Watz on 24.02.2025.
//

#include "CNFFormula.h"

long CNFFormula::getFileVarOf(long internalVar) {
    return internalToFileVar.at(internalVar);
}

long CNFFormula::getInternalVarOf(long fileVar) {
    return fileToInternalVar.at(fileVar);
}
