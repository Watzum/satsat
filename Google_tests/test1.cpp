//
// Created by Emil Watz on 20.02.2025.
//

#include "gtest/gtest.h"
#include "include/Dimacs.h"

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