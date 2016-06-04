#include "include/GeneralPurposeAlgorithms/IntegrationMethods/SimpsonsRule.h"

using namespace NumericMethods;

SimpsonsRule::SimpsonsRule(arma::mat &YPoints, double XRange)
    : IntegrationMethod(YPoints, XRange)
{

}

double SimpsonsRule::calculate()
{
    double Result, h, Sum = 0;
    h = XRange / (YPoints.size() - 1);

    for(size_t Cont = 1; Cont <= (YPoints.size() - 2); Cont++)
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
