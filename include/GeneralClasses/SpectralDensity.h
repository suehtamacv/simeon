#ifndef SPECTRALDENSITY_H
#define SPECTRALDENSITY_H

#include <GeneralClasses/TransferFunctions/TransferFunction.h>
#include <map>

class SpectralDensity
{
public:
    SpectralDensity(double freqMin, double freqMax, unsigned int numSamples);

    /**
     * @brief SBW_3dB is the bandwidth of a gaussian function of order 1 to 3 dB,
     * used on transmitedsignal spectral density calculations.
     */
    static constexpr double SBW_3dB = 40e9;
    static constexpr int GaussianOrder = 1;

    double densityScaling;

    double freqMin;
    double freqMax;

    arma::rowvec specDensity;
    std::map<std::pair<double, double>, arma::rowvec> specDensityMap;

    SpectralDensity &operator*=(TransferFunction &H);
};

#endif // SPECTRALDENSITY_H
