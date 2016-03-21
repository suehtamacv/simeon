#include "include/GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.h"

IntegrationMethod::IntegrationMethod(arma::mat &YPoints, double XRange)
    : YPoints(YPoints), XRange(XRange)
{

}

void IntegrationMethod::setValues(arma::mat &YP, double XR)
{
    YPoints = YP;
    XRange = XR;
}
