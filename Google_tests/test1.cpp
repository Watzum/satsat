//
// Created by Emil Watz on 20.02.2025.
//

#include "gtest/gtest.h"
#include "include/CNFFormula.h"
#include "include/Dimacs.h"
#include "include/DimacsFormatException.h"
#include "include/DimacsReader.h"

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
    CNFFormula rel;
    DimacsReader reader(rel);

    //ASSERT_NO_THROW(reader.readFile("../../Google_tests/dimacsFiles/DimacsTest1.dimacs"));
    reader.readFile("../../Google_tests/dimacsFiles/DimacsTest1.dimacs");
    //ASSERT_EQ(rel.getVariable(0).getNumberOfClauses(), 1);
    /*ASSERT_EQ(rel.getVariable(1).getNumberOfClauses(), 2);
    ASSERT_EQ(rel.getVariable(2).getNumberOfClauses(), 2);
    ASSERT_EQ(rel.getVariable(3).getNumberOfClauses(), 1);
    ASSERT_EQ(rel.getVariable(4).getNumberOfClauses(), 1);*/
}

TEST(Test1Suite, DimacsReaderDimacsFormatException_Test) {
    CNFFormula c;
    DimacsReader reader(c);

    for (int i = 1; i <= 8; i++) {
        std::string s = "../../Google_tests/dimacsFiles/DimacsThrow";
        s += std::to_string(i);
        s += ".dimacs";
        ASSERT_THROW(reader.readFile(s), DimacsFormatException);
    }
}

/*TEST(Test1Suite, CorrectFormulaRepresentation1) {
    DimacsReader reader;
    CNFFormula c{reader.readFile("../../Google_tests/dimacsFiles/DimacsTest2.dimacs")};
    //auto v = c.getClausesOfVariable(c.getInternalVarOf(1));
    auto v = c.getVariable(c.getInternalVarOf(1));

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
}*/