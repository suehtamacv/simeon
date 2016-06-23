#include "GeneralClasses/Transmittances/GaussianFilter.h"
#include <GeneralClasses/PhysicalConstants.h>

using namespace TF;

GaussianFilter::GaussianFilter(double centerFreq, unsigned int filterOrder, Gain scale) :
    Transmittance(scale), centerFreq(centerFreq), filterOrder(filterOrder)
{

}

double &GaussianFilter::get_CenterFreq()
{
    return centerFreq;
}

unsigned int &GaussianFilter::get_FilterOrder()
{
    return filterOrder;
}
