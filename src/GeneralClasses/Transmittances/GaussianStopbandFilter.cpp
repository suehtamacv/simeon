#include "include/GeneralClasses/Transmittances/GaussianStopbandFilter.h"

using namespace TF;

GaussianStopbandFilter::GaussianStopbandFilter
(double centerFreq, unsigned int filterOrder, Gain scale) :
    GaussianFilter(centerFreq, filterOrder, scale)
{

}

Gain GaussianStopbandFilter::get_TransmittanceAt(double freq)
{
    return Gain(1.0 - get_GaussianAt(freq).in_Linear(), Gain::Linear) + scale;
}
