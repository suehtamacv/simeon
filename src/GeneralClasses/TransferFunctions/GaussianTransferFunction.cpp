#include "GeneralClasses/TransferFunctions/GaussianTransferFunction.h"
#include <GeneralClasses/PhysicalConstants.h>

using namespace TF;

GaussianTransferFunction::GaussianTransferFunction
(double freqMin, double freqMax, unsigned long int numSamples,
 unsigned int order, double scale) :
    TransferFunction(freqMin, freqMax, numSamples, scale)
{
    double centerFreq = (freqMin + freqMax) / 2.0;
    for (auto& val : frequencySamples)
        {
        val = std::exp2l((-2) * pow(2 * (val - centerFreq) / BW_3dB, 2 * order));
        }
}
