#include "include/GeneralClasses/Transmittances/GaussianPassbandFilter.h"

using namespace TF;

GaussianPassbandFilter::GaussianPassbandFilter
(double centerFreq, unsigned int filterOrder, Gain scale) :
    GaussianFilter(centerFreq, filterOrder, scale)
{

}

Gain &GaussianPassbandFilter::get_TransmittanceAt(double freq)
{
    if (!calculatedGains.count(freq))
        {
        Gain G(std::exp2l(- pow(2 * (freq - centerFreq) / BW_3dB, 2 * filterOrder)), Gain::Linear);
        calculatedGains.emplace(freq, scale + G);
        }
    return calculatedGains.at(freq);
}
