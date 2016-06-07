#include "include/GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h"
#include <gtest/gtest.h>

using namespace NumericMethods;

TrapezoidalRule::TrapezoidalRule()
{

}

double TrapezoidalRule::calculate(const arma::mat &YPoints, double XRange)
{
    EXPECT_FALSE(YPoints.empty());
    double Result, Sum = 0, h;
    h = XRange / (YPoints.size() - 1);
    for(size_t Cont = 1; Cont <= (YPoints.size() - 2); Cont++)
        {
        Sum += YPoints.at(Cont);
        }

    Result = (h / 2) * (YPoints.at(YPoints.size() - 1) + YPoints.at(0) + 2 * Sum);
    return Result;
}
