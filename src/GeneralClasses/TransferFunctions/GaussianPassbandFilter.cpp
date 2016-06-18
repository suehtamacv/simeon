#include "include/GeneralClasses/TransferFunctions/GaussianPassbandFilter.h"

using namespace TF;

GaussianPassbandFilter::GaussianPassbandFilter
(double centerFreq, unsigned int filterOrder, Gain scale) :
    GaussianFilter(centerFreq, filterOrder, scale)
{

}

Gain GaussianPassbandFilter::get_TransmittanceAt(double freq)
{
    return get_GaussianAt(freq) + scale;
}
