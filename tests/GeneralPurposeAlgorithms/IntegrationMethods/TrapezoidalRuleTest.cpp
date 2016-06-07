#ifdef RUN_TESTS

#include "include/GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h"
#include <gtest/gtest.h>
#include <armadillo>

TEST(IntegrationMethodTest, TrapezoidalRule)
{
    NumericMethods::TrapezoidalRule TR;

    EXPECT_EQ(TR.calculate({0, 0, 0}, 100), 0) << "The integral of zero should be zero.";
    EXPECT_EQ(TR.calculate({1, 2, 3, 4}, 0), 0) << "The integral of a interval with zero length should be zero.";

    EXPECT_GT(TR.calculate({1, 2, 3}, 3.7), 0) << "The integral of a strictly positive function over a positive range should be positive.";
    EXPECT_LT(TR.calculate({ -1, -2, -3}, 3.7), 0) << "The integral of a strictly negative function over a positive range should be negative.";
    EXPECT_LT(TR.calculate({1, 2, 3}, -3.7), 0) << "The integral of a strictly positive function over a negative range should be negative.";
    EXPECT_GT(TR.calculate({ -1, -2, -3}, -3.7), 0) << "The integral of a strictly negative function over a negative range should be positive.";

    EXPECT_EQ(TR.calculate({1, 6, 3, 7}, 4), TR.calculate({ -1, -6, -3, -7}, -4)) << "The integral of -f(x) over -dx should be equal to the integral of f(x) over dx.";
    EXPECT_EQ(TR.calculate({1, 6, 3, 7}, 4), -TR.calculate({ -1, -6, -3, -7}, 4)) << "The integral of -f(x) over -dx should be minus the integral of f(x) over dx.";
}


#endif
