#include "include/GeneralPurposeAlgorithms/IntegrationMethods/SimpsonsRule.h"
#include <gtest/gtest.h>

using namespace NumericMethods;

SimpsonsRule::SimpsonsRule()
{

}

double SimpsonsRule::calculate(const arma::mat &YPoints, double XRange)
{
    EXPECT_FALSE(YPoints.empty());

    //Simpson rule only work to a even number of points.
    size_t numPoints = ((YPoints.size() % 2) == 0) ? YPoints.size() : YPoints.size() - 1;
    double Result, h, Sum = 0;
    h = XRange / (YPoints.size() - 1);

    for(size_t Cont = 1; Cont <= (numPoints - 2); Cont++)
        {
        if(Cont % 2)
            {
            Sum += 2 * YPoints.at(Cont);
            }
        else
            {
            Sum += 4 * YPoints.at(Cont);
            }
        }

    Result = (h / 3) * (YPoints.at(0) + Sum + YPoints.at(YPoints.size() - 1));
    return Result;
}
