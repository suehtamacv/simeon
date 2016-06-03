#ifndef GAUSSIANTRANSFERFUNCTION_H
#define GAUSSIANTRANSFERFUNCTION_H

#include <GeneralClasses/TransferFunctions/TransferFunction.h>

namespace TF
{
/**
 * @brief The GaussianTransferFunction class represents the impulse response of a Gaussian filter.
 */
class GaussianTransferFunction : public TransferFunction
{
public:
    /**
     * @brief GaussianTransferFunction is a constructor for a GaussianTransferFunction.
     * @param freqMin is the beginning of the signal's bandwidth.
     * @param freqMax is the end of the signal's bandwidth.
     * @param numSamples is the number of frequency samples along the bandwidth.
     * @param order is the order of this Gaussian function.
     * @param scale is the result of the gains and losses over this transfer function.
     */
    GaussianTransferFunction(double freqMin, double freqMax,
                             unsigned long int numSamples, unsigned int order, double scale);

    /**
     * @brief BW_3dB is the bandwidth of optical filter at 3 dB.
     */
    static constexpr double BW_3dB = 41e9;

};
}

#endif // GAUSSIANTRANSFERFUNCTION_H
