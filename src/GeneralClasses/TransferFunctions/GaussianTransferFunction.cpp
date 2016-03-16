#include "GeneralClasses/TransferFunctions/GaussianTransferFunction.h"
#include <GeneralClasses/PhysicalConstants.h>

GaussianTransferFunction::GaussianTransferFunction
(double freqMin, double freqMax, unsigned long int numSamples,
 unsigned int filterOrder, double scale) :
    TransferFunction(freqMin, freqMax, numSamples, scale)
{
    frequencySamples.transform(
        [&filterOrder] (double val)
        {
        return (std::exp(-2 * pow(2 * (val - PhysicalConstants::freq) / BW_3dB,
                                    2 * filterOrder)));
        }
    );
}
