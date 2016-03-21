#ifndef GAUSSIANTRANSFERFUNCTION_H
#define GAUSSIANTRANSFERFUNCTION_H

#include <GeneralClasses/TransferFunctions/TransferFunction.h>

class GaussianTransferFunction : public TransferFunction
{
public:
    GaussianTransferFunction(double freqMin, double freqMax,
                             unsigned long int numSamples, unsigned int filterOrder, double scale);

    /**
     * @brief BW_3dB is the bandwidth of optical filter at 3 dB.
     */
    static constexpr double BW_3dB = 40e9; // Perguntar se é 41e9 ou 40e9

};

#endif // GAUSSIANTRANSFERFUNCTION_H
