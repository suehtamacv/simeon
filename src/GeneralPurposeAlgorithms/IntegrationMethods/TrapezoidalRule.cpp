#include "include/GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h"

TrapezoidalRule::TrapezoidalRule(arma::mat &YPoints, double XRange)
    : IntegrationMethod(YPoints, XRange)
{

}

double TrapezoidalRule::Calculate()
{
    double Result, Sum = 0, h;
    h = XRange / (YPoints.size() - 1);
    for(unsigned int Cont = 1; Cont <= (YPoints.size() - 2); Cont++)
        {
        Sum += YPoints.at(Cont);
        }

    Result = (h / 2.0) * (2 * arma::accu(YPoints) - YPoints.begin() -
                          YPoints.end());
    Result = (h / 2) * (YPoints.at(YPoints.size() - 1) + YPoints.at(0) + 2 * Sum);
    return Result;
}
