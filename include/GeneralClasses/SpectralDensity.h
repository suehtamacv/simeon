#ifndef SPECTRALDENSITY_H
#define SPECTRALDENSITY_H

#include <GeneralClasses/Transmittances/Transmittance.h>
#include <map>
#include <memory>

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
     * @param cleanSpec is a flag for creating a rowvec of zeros as signal spectral density or not.
     */
    SpectralDensity(double freqMin, double freqMax, unsigned int numSamples, bool cleanSpec = false);
    SpectralDensity(const SpectralDensity &spec);
    /**
     * @brief SBW_3dB is the bandwidth of a gaussian function to 3 dB,
     * used on transmitted signal spectral density calculations.
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
    Gain densityScaling;
    /**
     * @brief freqMin is the beginning of the signal's bandwidth.
     */
    double freqMin;
    /**
     * @brief freqMax is the end of the signal's bandwidth.
     */
    double freqMax;
    /**
     * @brief stepFrequency is the step of the frequency values along the samples.
     */
    arma::rowvec specDensity;
    /**
     * @brief specDensityMap is a cache of the spectral density's possible values, given a set of freqMin and freqMax.
     */
    double stepFrequency;
    /**
     * @brief specDensity is a vector of this spectral density's samples.
     */
    static std::map<std::pair<double, double>, arma::rowvec> specDensityMap;
    /**
     * @brief operator *= applies a TransferFunction over this SpectralDensity.
     * @param H is the TransferFunction.
     * @return a reference to this object.
     */
    SpectralDensity& operator*=(std::shared_ptr<TF::Transmittance> H);
    SpectralDensity operator*(std::shared_ptr<TF::Transmittance> H) const;
    SpectralDensity& operator+=(const SpectralDensity &);
    bool operator==(const SpectralDensity &) const;
};

#endif // SPECTRALDENSITY_H
