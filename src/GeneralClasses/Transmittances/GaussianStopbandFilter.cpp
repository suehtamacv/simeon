#include "include/GeneralClasses/Transmittances/GaussianStopbandFilter.h"

using namespace TF;

GaussianStopbandFilter::GaussianStopbandFilter
(double centerFreq, unsigned int filterOrder, Gain scale) :
    GaussianFilter(centerFreq, filterOrder, scale)
{

}

Gain &GaussianStopbandFilter::get_TransmittanceAt(double freq)
{
    if (!calculatedGains.count(freq))
        {
        Gain G(std::exp2l(- pow(2 * (freq - centerFreq) / BW_3dB, 2 * filterOrder)), Gain::Linear);
        calculatedGains.emplace(freq, Gain(1.0 - G.in_Linear(), Gain::Linear) + scale);
        }
    return calculatedGains.at(freq);
}
