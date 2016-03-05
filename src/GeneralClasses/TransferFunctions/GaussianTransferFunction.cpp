#include "GeneralClasses/TransferFunctions/GaussianTransferFunction.h"
#include <GeneralClasses/PhysicalConstants.h>

GaussianTransferFunction::GaussianTransferFunction(double freqMin,
        double freqMax, unsigned long int numSamples,
        unsigned int filterOrder) : TransferFunction(freqMin,
                    freqMax, numSamples)
{
    frequencySamples.transform(
        [&filterOrder] (double val)
        {
        return (std::exp2l(-2 * pow(2 * (val - PhysicalConstants::freq) / BW_3dB,
                                    2 * filterOrder)));
        }
    );
}
