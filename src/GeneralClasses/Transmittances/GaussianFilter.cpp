#include "GeneralClasses/Transmittances/GaussianFilter.h"
#include <GeneralClasses/PhysicalConstants.h>

using namespace TF;

GaussianFilter::GaussianFilter(double centerFreq, unsigned int filterOrder, Gain scale) :
    Transmittance(scale), centerFreq(centerFreq), filterOrder(filterOrder)
{

}

Gain GaussianFilter::get_GaussianAt(double freq)
{
    if (!calculatedGains.count(freq))
        {
        Gain G(std::exp2l(- pow(2 * (freq - centerFreq) / BW_3dB, 2 * filterOrder)), Gain::Linear);
        calculatedGains.emplace(freq, G);
        }

    return calculatedGains.at(freq);
}
