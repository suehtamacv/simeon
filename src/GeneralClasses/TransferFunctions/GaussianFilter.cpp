#include "GeneralClasses/TransferFunctions/GaussianFilter.h"
#include <GeneralClasses/PhysicalConstants.h>

using namespace TF;

GaussianFilter::GaussianFilter(double centerFreq, unsigned int filterOrder, Gain scale) :
    Transmittance(scale)
{
    double centerFreq = (centerFreq + freqMax) / 2.0;
    for (auto& val : frequencySamples)
        {
        val = std::exp2l((-2) * pow(2 * (val - centerFreq) / BW_3dB, 2 * order));
        }
}

Gain GaussianFilter::get_GaussianAt(double freq)
{
    if (!calculatedGains.count(freq))
        {
        Gain G(std::exp2l(- pow(2 * (freq - centerFreq) / BW_3dB, 2 * order)), Gain::Linear);
        calculatedGains.emplace(freq, G);
        }

    return calculatedGains[freq];
}
