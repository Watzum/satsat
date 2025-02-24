//
// Created by Emil Watz on 20.02.2025.
//

#include "gtest/gtest.h"
#include "include/Dimacs.h"
#include "include/DimacsFormatException.h"
#include "include/DimacsReader.h"
#include "include/VariableClauseRelation.h"

TEST(Test1Suite, to_positive_long) {
    ASSERT_EQ(dimacs::to_positive_long("1"), 1);
    ASSERT_EQ(dimacs::to_positive_long("123"), 123);
    ASSERT_EQ(dimacs::to_positive_long("123456789"), 123456789);

    ASSERT_THROW(dimacs::to_positive_long(""), DimacsFormatException);

    ASSERT_THROW(dimacs::to_positive_long("a123"), DimacsFormatException);
    ASSERT_THROW(dimacs::to_positive_long("123y"), DimacsFormatException);
    ASSERT_THROW(dimacs::to_positive_long("1b23"), DimacsFormatException);
    ASSERT_THROW(dimacs::to_positive_long("-123"), DimacsFormatException);
    ASSERT_THROW(dimacs::to_positive_long("5456.4"), DimacsFormatException);
}

TEST(Test1Suite, DimacsReader_Positive1) {
    VariableClauseRelation rel;
    DimacsReader reader{rel};

    ASSERT_NO_THROW(reader.readFile("../../Google_tests/dimacsFiles/DimacsTest1.dimacs"));
    ASSERT_EQ(rel.getClausesOfVariable(0).size(), 1);
    ASSERT_EQ(rel.getClausesOfVariable(1).size(), 2);
    ASSERT_EQ(rel.getClausesOfVariable(2).size(), 2);
    ASSERT_EQ(rel.getClausesOfVariable(3).size(), 1);
    ASSERT_EQ(rel.getClausesOfVariable(4).size(), 1);
}

TEST(Test1Suite, DimacsReader_DimacsFormatException_Test) {
    VariableClauseRelation rel;
    DimacsReader reader{rel};

    for (int i = 1; i <= 8; i++) {
        std::string s = "../../Google_tests/dimacsFiles/DimacsThrow";
        s += std::to_string(i);
        s += ".dimacs";
        ASSERT_THROW(reader.readFile(s), DimacsFormatException);
    }
}

TEST(Test1Suite, CNFFormula_FileToInternalVarMap) {
    VariableClauseRelation rel;
    DimacsReader reader{rel};
    CNFFormula c{reader.readFile("../../Google_tests/dimacsFiles/DimacsInternalRep1.dimacs")};
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(15)), 15);
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(7)), 7);
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(8)), 8);
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(32)), 32);
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(1)), 1);
}