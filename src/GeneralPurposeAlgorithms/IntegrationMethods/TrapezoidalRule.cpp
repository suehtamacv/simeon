#include "include/GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h"

TrapezoidalRule::TrapezoidalRule(arma::mat &YPoints, double XRange)
    : IntegrationMethod(YPoints, XRange)
{

}

double TrapezoidalRule::Calculate()
{
    double h = XRange / (YPoints.size() - 1);
    return (h / 2.0) * (2 * arma::accu(YPoints) -
                        *YPoints.begin() - *YPoints.end());
}
