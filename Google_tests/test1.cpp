//
// Created by Emil Watz on 20.02.2025.
//

#include "gtest/gtest.h"
#include "include/Dimacs.h"
#include "include/DimacsFormatException.h"
#include "include/DimacsReader.h"
#include "include/VariableClauseRelation.h"

TEST(Test1Suite, ToPositiveLong) {
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

TEST(Test1Suite, DimacsReaderPositive1) {
    DimacsReader reader;

    //ASSERT_NO_THROW(reader.readFile("../../Google_tests/dimacsFiles/DimacsTest1.dimacs"));
    CNFFormula rel = reader.readFile("../../Google_tests/dimacsFiles/DimacsTest1.dimacs");
    ASSERT_EQ(rel.getClausesOfVariable(0).size(), 1);
    ASSERT_EQ(rel.getClausesOfVariable(1).size(), 2);
    ASSERT_EQ(rel.getClausesOfVariable(2).size(), 2);
    ASSERT_EQ(rel.getClausesOfVariable(3).size(), 1);
    ASSERT_EQ(rel.getClausesOfVariable(4).size(), 1);
}

TEST(Test1Suite, DimacsReaderDimacsFormatException_Test) {
    DimacsReader reader;

    for (int i = 1; i <= 8; i++) {
        std::string s = "../../Google_tests/dimacsFiles/DimacsThrow";
        s += std::to_string(i);
        s += ".dimacs";
        ASSERT_THROW(reader.readFile(s), DimacsFormatException);
    }
}

TEST(Test1Suite, FileToInternalVarMap) {
    DimacsReader reader;
    CNFFormula c{reader.readFile("../../Google_tests/dimacsFiles/DimacsInternalRep1.dimacs")};
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(15)), 15);
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(7)), 7);
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(8)), 8);
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(32)), 32);
    ASSERT_EQ(c.getFileVarOf(c.getInternalVarOf(1)), 1);
}

TEST(Test1Suite, VariableClauseRelation) {
    VariableClauseRelation r;
    ASSERT_EQ(r.addClause(), 0);
}

TEST(Test1Suite, CorrectFormulaRepresentation1) {
    DimacsReader reader;
    CNFFormula c{reader.readFile("../../Google_tests/dimacsFiles/DimacsTest2.dimacs")};
    auto v = c.getClausesOfVariable(c.getInternalVarOf(1));
    ASSERT_EQ(v.at(0).first, 0);
    ASSERT_EQ(v.at(0).second, true);
    ASSERT_EQ(v.size(), 1);

    v = c.getClausesOfVariable(c.getInternalVarOf(2));
    ASSERT_EQ(v.at(0).first, 0);
    ASSERT_EQ(v.at(0).second, true);
    ASSERT_EQ(v.at(1).first, 1);
    ASSERT_EQ(v.at(1).second, false);

    v = c.getClausesOfVariable(c.getInternalVarOf(3));
    ASSERT_EQ(v.at(0).first, 0);
    ASSERT_EQ(v.at(0).second, false);
    ASSERT_EQ(v.at(1).first, 1);
    ASSERT_EQ(v.at(1).second, true);

    v = c.getClausesOfVariable(c.getInternalVarOf(4));
    ASSERT_EQ(v.at(0).first, 1);
    ASSERT_EQ(v.at(0).second, true);
    ASSERT_EQ(v.at(1).first, 2);
    ASSERT_EQ(v.at(1).second, false);

    v = c.getClausesOfVariable(c.getInternalVarOf(5));
    ASSERT_EQ(v.at(0).first, 1);
    ASSERT_EQ(v.at(0).second, true);
    ASSERT_EQ(v.at(1).first, 2);
    ASSERT_EQ(v.at(1).second, false);
}

TEST(Test1Suite, CorrectFormulaRepresentation2) {
    DimacsReader reader;
    CNFFormula c{reader.readFile("../../Google_tests/dimacsFiles/DimacsTest2.dimacs")};
    auto v = c.getVariablesOfClause(0);
    ASSERT_EQ(v.at(0).first, c.getInternalVarOf(1));
    ASSERT_EQ(v.at(0).second, true);
    ASSERT_EQ(v.at(1).first, c.getInternalVarOf(2));
    ASSERT_EQ(v.at(1).second, true);
    ASSERT_EQ(v.at(2).first, c.getInternalVarOf(3));
    ASSERT_EQ(v.at(2).second, false);
    ASSERT_EQ(v.size(), 3);
    v = c.getVariablesOfClause(1);
    ASSERT_EQ(v.at(0).first, c.getInternalVarOf(4));
    ASSERT_EQ(v.at(0).second, true);
    ASSERT_EQ(v.at(1).first, c.getInternalVarOf(2));
    ASSERT_EQ(v.at(1).second, false);
    ASSERT_EQ(v.at(2).first, c.getInternalVarOf(5));
    ASSERT_EQ(v.at(2).second, true);
    ASSERT_EQ(v.at(3).first, c.getInternalVarOf(3));
    ASSERT_EQ(v.at(3).second, true);
    ASSERT_EQ(v.size(), 4);
    v = c.getVariablesOfClause(2);
    ASSERT_EQ(v.at(0).first, c.getInternalVarOf(4));
    ASSERT_EQ(v.at(0).second, false);
    ASSERT_EQ(v.at(1).first, c.getInternalVarOf(5));
    ASSERT_EQ(v.at(1).second, false);
    ASSERT_EQ(v.size(), 2);
}