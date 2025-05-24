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
    std::vector<size_t> mapping = reader.readFile("../../Google_tests/dimacsFiles/DimacsTest1.dimacs");
    ASSERT_EQ(rel.getVariable(0).getNumberOfClauses(), 1);
    ASSERT_EQ(rel.getVariable(1).getNumberOfClauses(), 2);
    ASSERT_EQ(rel.getVariable(2).getNumberOfClauses(), 2);
    ASSERT_EQ(rel.getVariable(3).getNumberOfClauses(), 1);
    ASSERT_EQ(rel.getVariable(4).getNumberOfClauses(), 1);

    Clause& c1 = rel.getClause(0);
    int count = 0;
    for (auto it = c1.begin(); it != c1.end(); ++it) {
        count++;
    }
    ASSERT_EQ(count, 3);

    c1 = rel.getClause(1);
    count = 0;
    for (auto it = c1.begin(); it != c1.end(); ++it) {
        count++;
    }
    ASSERT_EQ(count, 4);
}

TEST(Test1Suite, DimacsReaderPositive2) {
    CNFFormula rel;
    DimacsReader reader(rel);
    std::vector<size_t> mapping = reader.readFile("../../Google_tests/dimacsFiles/DimacsTest2.dimacs");
    ASSERT_EQ(rel.getVariable(0).getNumberOfClauses(), 1);
    ASSERT_EQ(rel.getVariable(1).getNumberOfClauses(), 2);
    ASSERT_EQ(rel.getVariable(2).getNumberOfClauses(), 2);
    ASSERT_EQ(rel.getVariable(3).getNumberOfClauses(), 2);
    ASSERT_EQ(rel.getVariable(4).getNumberOfClauses(), 2);

    Clause& c1 = rel.getClause(0);
    int count = 0;
    for (auto it = c1.begin(); it != c1.end(); ++it) {
        count++;
    }
    ASSERT_EQ(count, 3);

    c1 = rel.getClause(1);
    count = 0;
    for (auto it = c1.begin(); it != c1.end(); ++it) {
        count++;
    }
    ASSERT_EQ(count, 4);

    c1 = rel.getClause(2);
    count = 0;
    for (auto it = c1.begin(); it != c1.end(); ++it) {
        count++;
    }
    ASSERT_EQ(count, 2);
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

TEST(Test1Suite, CNFFormulaCopyConstructor) {
    CNFFormula f;
    CNFFormula f1 = f;
    auto c = f.addNewClause();
    auto v = f.addNewVariable();
    f.addVariableToClause(v, c, true);
    ASSERT_TRUE(f1.isEmptySet());

    CNFFormula f2 = f;
    Variable& var = f.getVariable(v);
    var.removeClause(c);

    ASSERT_EQ(f.getVariable(v).getNumberOfClauses(), 0);
    ASSERT_EQ(f2.getVariable(v).getNumberOfClauses(), 1);

    CNFFormula f3 = f2;
    f2.getClause(c).removeVariable(v);
    ASSERT_TRUE(f2.getClause(c).isEmpty());
    ASSERT_TRUE(!f3.getClause(c).isEmpty());
}

TEST(Test1Suite, CNFFormulaAssignment) {
    CNFFormula f;
    auto c1 = f.addNewClause();

    auto v1 = f.addNewVariable();
    auto v2 = f.addNewVariable();

    f.addVariableToClause(v1, c1, true);
    f.addVariableToClause(v2, c1, false);

    f.assignVariable(v1, false);
    ASSERT_TRUE(f.getAssignmentState() == dimacs::UNKNOWN);
    f.assignVariable(v2, true);
    ASSERT_TRUE(f.getAssignmentState() == dimacs::FALSE);

    CNFFormula f2;

    c1 = f2.addNewClause();

    v1 = f2.addNewVariable();
    f2.addVariableToClause(v1, c1, true);

    CNFFormula f3 = f2;
    f2.assignVariable(v1, true);
    f3.assignVariable(v1, false);
    ASSERT_TRUE(f2.isEmptySet());
    ASSERT_FALSE(f3.isEmptySet());
}


TEST(Test1Suite, ClauseAssignmentTest1) {
    Clause c;
    ASSERT_TRUE(c.isEmpty());
    ASSERT_FALSE(c.isSatisfied());
    c.addVariable(0, true);
    ASSERT_FALSE(c.isEmpty());
    ASSERT_FALSE(c.isSatisfied());
    c.addVariableAssignment(0, true);
    ASSERT_TRUE(c.isSatisfied());
    ASSERT_FALSE(c.isEmpty());
    c.removeVariableAssignment(0, true);
    ASSERT_FALSE(c.isEmpty());
    ASSERT_FALSE(c.isSatisfied());
    c.addVariableAssignment(0, false);
    ASSERT_FALSE(c.isSatisfied());
    ASSERT_TRUE(c.isEmpty());
}

TEST(Test1Suite, ClauseAssignmentTest2) {
    Clause c;
    c.addVariable(0, true);
    c.addVariable(1, false);
    c.addVariable(2, true);
    c.addVariableAssignment(0, false);
    c.addVariableAssignment(1, true);
    ASSERT_FALSE(c.isEmpty());
    ASSERT_FALSE(c.isSatisfied());
    c.addVariableAssignment(2, true);
    ASSERT_FALSE(c.isEmpty());
    ASSERT_TRUE(c.isSatisfied());
    c.removeVariableAssignment(2, true);
    ASSERT_TRUE(!c.isSatisfied() && !c.isEmpty());
    c.addVariableAssignment(2, false);
    ASSERT_TRUE(c.isEmpty() && !c.isSatisfied());
}

TEST(Test1Suite, CNFAssignmentTest1) {
    CNFFormula f;
    auto c1 = f.addNewClause();
    auto v1 = f.addNewVariable();
    f.addVariableToClause(v1, c1, true);
    f.assignVariable(v1, true);
    ASSERT_TRUE(f.getAssignmentState() == dimacs::TRUE);
    f.revokeVariableAssignment(v1);
    f.assignVariable(v1, false);
    ASSERT_TRUE(f.getAssignmentState() == dimacs::FALSE);
}

TEST(Test1Suite, UnitClauseAssignmentTest1) {
    CNFFormula f;
    auto c1 = f.addNewClause();
    auto c2 = f.addNewClause();
    auto v1 = f.addNewVariable();
    auto v2 = f.addNewVariable();
    f.addVariableToClause(c1, v1, true);
    f.addVariableToClause(c2, v2, false);
    f.assignUnitClauses();
    ASSERT_TRUE(f.getAssignmentState() == dimacs::TRUE);

    CNFFormula f2;
    c1 = f2.addNewClause();
    c2 = f2.addNewClause();
    v1 = f2.addNewVariable();
    v2 = f2.addNewVariable();
    f2.addVariableToClause(v1, c1, true);
    f2.addVariableToClause(v2, c1, false);
    f2.addVariableToClause(v1, c2, false);
    f2.addVariableToClause(v2, c2, false);
    f2.assignVariable(v1, true);
    f2.assignUnitClauses();
    ASSERT_TRUE(f2.getAssignmentState() == dimacs::TRUE);

    CNFFormula f3;
    c1 = f3.addNewClause();
    c2 = f3.addNewClause();
    v1 = f3.addNewVariable();
    v2 = f3.addNewVariable();
    f3.addVariableToClause(v1, c1, true);
    f3.addVariableToClause(v2, c2, false);
    f3.addVariableToClause(v1, c2, false);
    f3.assignUnitClauses();
    ASSERT_TRUE(f3.getAssignmentState() == dimacs::TRUE);
}

TEST(Test1Suite, resetAssignmentTest) {
    CNFFormula f;
    auto v1 = f.addNewVariable();
    auto c1 = f.addNewClause();
    f.addVariableToClause(v1, c1, true);
    f.resetAssignment();
    ASSERT_TRUE(f.getAssignmentState() == dimacs::UNKNOWN);
    f.assignVariable(v1, true);
    f.resetAssignment();
    ASSERT_TRUE(f.getAssignmentState() == dimacs::UNKNOWN);
}


TEST(Test1Suite, dimacsCommentTest) {
    CNFFormula c;
    DimacsReader r{c};
    ASSERT_NO_THROW(r.readFile("../../Google_tests/dimacsFiles/DimacsComments1.dimacs"));
    ASSERT_NO_THROW(r.readFile("../../Google_tests/dimacsFiles/DimacsComments2.dimacs"));
    ASSERT_NO_THROW(r.readFile("../../Google_tests/dimacsFiles/DimacsComments3.dimacs"));
}