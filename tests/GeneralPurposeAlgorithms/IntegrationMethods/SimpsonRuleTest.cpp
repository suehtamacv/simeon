#ifdef RUN_TESTS

#include <gtest/gtest.h>
#include "GeneralPurposeAlgorithms/IntegrationMethods/SimpsonsRule.h"
#include <armadillo>

TEST(SimpsonMethodTest, SimpsonRule)
{
    NumericMethods::SimpsonsRule SR;

    EXPECT_EQ(SR.calculate({0, 0, 0}, 100), 0) << "The integral of zero should be zero.";
    EXPECT_EQ(SR.calculate({1, 2, 3, 4}, 0), 0) << "The integral of a interval with zero length should be zero.";

    EXPECT_GT(SR.calculate({1, 2, 3}, 3.7), 0) << "The integral of a strictly positive function over a positive range should be positive.";
    EXPECT_LT(SR.calculate({ -1, -2, -3}, 3.7), 0) << "The integral of a strictly negative function over a positive range should be negative.";
    EXPECT_LT(SR.calculate({1, 2, 3}, -3.7), 0) << "The integral of a strictly positive function over a negative range should be negative.";
    EXPECT_GT(SR.calculate({ -1, -2, -3}, -3.7), 0) << "The integral of a strictly negative function over a negative range should be positive.";

    EXPECT_EQ(SR.calculate({1, 6, 3, 7}, 4), SR.calculate({ -1, -6, -3, -7}, -4)) << "The integral of -f(x) over -dx should be equal to the integral of f(x) over dx.";
    EXPECT_EQ(SR.calculate({1, 6, 3, 7}, 4), -SR.calculate({ -1, -6, -3, -7}, 4)) << "The integral of -f(x) over -dx should be minus the integral of f(x) over dx.";
}
#endif
