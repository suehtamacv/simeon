#include "include/GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.h"

IntegrationMethod::IntegrationMethod(std::vector<double> YPoints, double XRange)
    : YPoints(YPoints), XRange(XRange)
{

}

void IntegrationMethod::setValues(std::vector<double> YP, double XR)
{
    YPoints = YP;
    XRange = XR;
}
