#ifndef SPECTRALDENSITY_H
#define SPECTRALDENSITY_H

#include <GeneralClasses/TransferFunctions/TransferFunction.h>
#include <map>

/**
 * @brief The SpectralDensity class represents the elements related to a signal's spectral density.
 */
class SpectralDensity
{
public:
    /**
     * @brief SpectralDensity is a constructor for a SpectralDensity.
     * @param freqMin is the beginning of the signal's bandwidth.
     * @param freqMax is the end of the signal's bandwidth.
     * @param numSamples is the number of frequency samples along the bandwidth.
     */
    SpectralDensity(double freqMin, double freqMax, unsigned int numSamples, bool cleanSpec = false);

    /**
     * @brief SBW_3dB is the bandwidth of a gaussian function of order 1 to 3 dB,
     * used on transmitedsignal spectral density calculations.
     */
    static constexpr double SBW_3dB = 40e9;
    /**
     * @brief TxFilterOrder is the optical filter order for the transmitted signal.
     */
    static int TxFilterOrder;
    /**
     * @brief GaussianOrder is the order of the SSSs optical filters along the route.
     */
    static int GaussianOrder;
    /**
     * @brief define_SignalsFilterOrder is used to set TxFilterOrder and GaussianOrder values.
     */
    static void define_SignalsFilterOrder();
    /**
     * @brief densityScaling is the result of the gains and losses over this spectral density.
     */
    double densityScaling;
    /**
     * @brief freqMin is the beginning of the signal's bandwidth.
     */
    double freqMin;
    /**
     * @brief freqMax is the end of the signal's bandwidth.
     */
    double freqMax;
    /**
     * @brief specDensity is a vector of this spectral density's samples.
     */
    arma::rowvec specDensity;
    /**
     * @brief specDensityMap is a cache of the spectral density's possible values, given a set of freqMin and freqMax.
     */
    static std::map<std::pair<double, double>, arma::rowvec> specDensityMap;
    /**
     * @brief operator *= applies a TransferFunction over this SpectralDensity.
     * @param H is the TransferFunction.
     * @return a reference to this object.
     */
    SpectralDensity &operator*=(TF::TransferFunction &H);
};

#endif // SPECTRALDENSITY_H
