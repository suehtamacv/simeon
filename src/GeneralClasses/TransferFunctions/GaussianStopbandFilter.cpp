#include "include/GeneralClasses/TransferFunctions/GaussianStopbandFilter.h"

using namespace TF;

GaussianStopbandFilter::GaussianStopbandFilter
(double centerFreq, unsigned int filterOrder, Gain scale) :
    GaussianFilter(centerFreq, filterOrder, scale)
{

}

Gain GaussianStopbandFilter::get_TransmittanceAt(double freq)
{
    return scale + Gain(1.0 - get_TransmittanceAt(freq).in_Linear(), Gain::Linear);
}
