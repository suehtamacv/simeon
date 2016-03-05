#include "GeneralClasses/SpectralDensity.h"
#include <GeneralClasses/PhysicalConstants.h>

SpectralDensity::SpectralDensity
(double freqMin, double freqMax, unsigned int numSamples) :
    specDensity(arma::linspace(freqMin, freqMax, numSamples).t()), densityScaling(1)
{
    specDensity.transform(
        [] (double val)
        {
        return (std::exp2l(-pow(2 * (val - PhysicalConstants::freq) / SBW_3dB,
                                2 * GaussianOrder)));
        }
    );
}

SpectralDensity& SpectralDensity::operator *=(TransferFunction &H)
{
    densityScaling *= H.scale;
    if (!H.isImpulseTransferFunction)
        {
        specDensity %= H.frequencySamples;
        }

    return *this;
}
