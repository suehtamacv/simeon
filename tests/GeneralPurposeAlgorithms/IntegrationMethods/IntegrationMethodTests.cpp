#ifdef RUN_TESTS

#include <gtest/gtest.h>
#include "GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h"
#include "GeneralPurposeAlgorithms/IntegrationMethods/SimpsonsRule.h"
#include <armadillo>

using namespace NumericMethods;

TEST(IntegrationMethodTest, TrapezoidalRule)
{
    arma::mat yPoints = {0, 0, 0};
    double XRange = 100;
    TrapezoidalRule TR(yPoints, XRange);

    ASSERT_EQ(TR.YPoints.n_cols, yPoints.n_cols) << "Y Points do not have equal length.";
    for (size_t c = 0; c < yPoints.n_cols; ++c)
        {
        EXPECT_EQ(TR.YPoints[c], yPoints[c]) << "Y Points differ at position " << c << ".";
        }
    EXPECT_EQ(TR.XRange, XRange) << "X Range not being correctly set.";

    EXPECT_EQ(TR.calculate(), 0) << "The integral of zero should be zero.";

    yPoints = {1, 2, 3};
    XRange = 15;
    TR.setValues(yPoints, XRange);
    ASSERT_EQ(TR.YPoints.n_cols, yPoints.n_cols) << "Y Points do not have equal length.";
    for (size_t c = 0; c < yPoints.n_cols; ++c)
        {
        EXPECT_EQ(TR.YPoints[c], yPoints[c]) << "Y Points differ at position " << c << ".";
        }
    EXPECT_EQ(TR.XRange, XRange) <<  "X Range not being correctly set.";
    EXPECT_GT(TR.calculate(), 0) << "The integral of a positive function should be positive.";

    yPoints = {-1, -2, -3};
    XRange = 15;
    TR.setValues(yPoints, XRange);
    EXPECT_LT(TR.calculate(), 0) << "The integral of a negative function should be negative.";

    yPoints = {-1, -2, -3};
    XRange = -15;
    TR.setValues(yPoints, XRange);
    EXPECT_GT(TR.calculate(), 0) << "The integral of a negative function over a negative range should be positive.";

    yPoints = {1, 2, 3};
    XRange = 0;
    TR.setValues(yPoints, XRange);
    EXPECT_EQ(TR.calculate(), 0) << "The integral of a interval with zero length should be zero.";
}

TEST(IntegrationMethodTest, SimpsonRule)
{
    arma::mat yPoints = {0, 0, 0};
    double XRange = 100;
    SimpsonsRule SR(yPoints, XRange);

    ASSERT_EQ(SR.YPoints.n_cols, yPoints.n_cols) << "Y Points do not have equal length.";
    for (size_t c = 0; c < yPoints.n_cols; ++c)
        {
        EXPECT_EQ(SR.YPoints[c], yPoints[c]) << "Y Points differ at position " << c << ".";
        }
    EXPECT_EQ(SR.XRange, XRange) << "X Range not being correctly set.";

    EXPECT_EQ(SR.calculate(), 0) << "The integral of zero should be zero.";

    yPoints = {1, 2, 3};
    XRange = 15;
    SR.setValues(yPoints, XRange);
    ASSERT_EQ(SR.YPoints.n_cols, yPoints.n_cols) << "Y Points do not have equal length.";
    for (size_t c = 0; c < yPoints.n_cols; ++c)
        {
        EXPECT_EQ(SR.YPoints[c], yPoints[c]) << "Y Points differ at position " << c << ".";
        }
    EXPECT_EQ(SR.XRange, XRange) <<  "X Range not being correctly set.";
    EXPECT_GT(SR.calculate(), 0) << "The integral of a positive function should be positive.";

    yPoints = {-1, -2, -3};
    XRange = 15;
    SR.setValues(yPoints, XRange);
    EXPECT_LT(SR.calculate(), 0) << "The integral of a negative function should be negative.";

    yPoints = {-1, -2, -3};
    XRange = -15;
    SR.setValues(yPoints, XRange);
    EXPECT_GT(SR.calculate(), 0) << "The integral of a negative function over a negative range should be positive.";

    yPoints = {1, 2, 3};
    XRange = 0;
    SR.setValues(yPoints, XRange);
    EXPECT_EQ(SR.calculate(), 0) << "The integral of a interval with zero length should be zero.";
}

#endif
