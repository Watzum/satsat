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

    ASSERT_THROW(dimacs::to_positive_long(""), std::invalid_argument);

    ASSERT_THROW(dimacs::to_positive_long("a123"), std::invalid_argument);
    ASSERT_THROW(dimacs::to_positive_long("123y"), std::invalid_argument);
    ASSERT_THROW(dimacs::to_positive_long("1b23"), std::invalid_argument);
    ASSERT_THROW(dimacs::to_positive_long("-123"), std::invalid_argument);
    ASSERT_THROW(dimacs::to_positive_long("5456.4"), std::invalid_argument);
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

TEST(Test1Suite, DimacsReader_Throw1) {
    VariableClauseRelation rel;
    DimacsReader reader{rel};

    ASSERT_THROW(reader.readFile("../../Google_tests/dimacsFiles/DimacsThrow1.dimacs"), DimacsFormatException);
    ASSERT_THROW(reader.readFile("../../Google_tests/dimacsFiles/DimacsThrow2.dimacs"), DimacsFormatException);
    ASSERT_THROW(reader.readFile("../../Google_tests/dimacsFiles/DimacsThrow3.dimacs"), DimacsFormatException);
    ASSERT_THROW(reader.readFile("../../Google_tests/dimacsFiles/DimacsThrow4.dimacs"), DimacsFormatException);
}