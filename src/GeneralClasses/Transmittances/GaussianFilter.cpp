#include "GeneralClasses/Transmittances/GaussianFilter.h"
#include <GeneralClasses/PhysicalConstants.h>

using namespace TF;

GaussianFilter::GaussianFilter(double centerFreq, unsigned int filterOrder, Gain scale) :
    Transmittance(scale), centerFreq(centerFreq), filterOrder(filterOrder)
{

}
