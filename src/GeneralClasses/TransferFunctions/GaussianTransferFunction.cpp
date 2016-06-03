#include "GeneralClasses/TransferFunctions/GaussianTransferFunction.h"
#include <GeneralClasses/PhysicalConstants.h>

using namespace TF;

GaussianTransferFunction::GaussianTransferFunction
(double freqMin, double freqMax, unsigned long int numSamples,
 unsigned int order, double scale) :
    TransferFunction(freqMin, freqMax, numSamples, scale)
{
    for (auto& val : frequencySamples)
        {
        val = std::exp2l((-2) * pow(2 * (val - PhysicalConstants::freq) / BW_3dB,
                                    2 * order));
        }
}
