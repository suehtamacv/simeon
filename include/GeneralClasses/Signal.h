#ifndef SIGNAL_H
#define SIGNAL_H

#include <GeneralClasses/Power.h>
#include <GeneralClasses/SpectralDensity.h>
#include <vector>
#include <memory>
#include <map>

extern bool considerAseNoise;
extern bool considerFilterImperfection;

/**
 * @brief The Signal class represents a signal that propagates through the
 * network.
 */
class Signal
{
public:
    /**
     * @brief InputOSNR is the input OSNR of the network.
     */
    static Gain InputOSNR;
    /**
     * @brief InputPower is the input power of the network transmitters.
     */
    static Power InputPower;

    /**
     * @brief Signal is the standard constructor of a Signal. Creates a signal
     * with power InputPower and OSNR InputOSNR.
     */
    Signal(unsigned int numSlots = 1);
    /**
     * @brief operator *= multiplies the Signal by a gain, effectively rescaling
     * both the signal and the noise.
     * @return a signal after the application of the gain.
     */
    Signal &operator *=(Gain &);
    /**
     * @brief operator += adds a noise power to the current NoisePower.
     * @return a signal after adding the noise.
     */
    Signal &operator +=(Power &);
    /**
     * @brief operator *= multiplies this signal spectral density by a transfer function.
     * @return a signal after the transfer function.
     */
    Signal &operator *=(TransferFunction &);
    /**
     * @brief get_OSNR returns the Signal-To-Noise Ratio of the Signal.
     * @return the Signal-To-Noise Ratio of the Signal.
     */
    Gain get_OSNR();
    /**
     * @brief get_NoisePower returns the Noise Power of the Signal.
     * @return the Noise Power of the Signal.
     */
    Power get_NoisePower();
    /**
     * @brief get_SpectralPower returns the power of the Signal along a spectral density curve.
     * @return the power of the Signal along a spectral density curve.
     */
    Power get_SpectralPower();
    /**
     * @brief get_SignalPowerRatio returns the ratio of this signal's original and final spectral density power.
     * @return the ratio of this signal's original and final spectral density power.
     */
    double get_SignalPowerRatio();
    /**
     * @brief get_PowerRatioThreshold returns the power ratio threshold for blocking a call.
     * @return the power ratio threshold for blocking a call.
     */
    double get_PowerRatioThreshold();
    /**
     * @brief numFrequencySamples number of samples along the signal's bandwidth.
     */
    static constexpr unsigned long numFrequencySamples = 25;
    /**
     * @brief numSlots is the number of slots occupied by this Signal.
     */
    unsigned int numSlots;

private:
    Power SignalPower;
    Power NoisePower;
    /**
     * @brief frequencyRange is half of the signal's bandwith.
     */
    double frequencyRange;
    /**
     * @brief originalSpecDensityCache is a map with the spectral density power of a signal, given a number of slots.
     */
    std::map<int, Power> originalSpecDensityCache ;
    /**
     * @brief signalSpecDensity is this signal's spectral density.
     */
    std::shared_ptr<SpectralDensity> signalSpecDensity;

};

#endif // SIGNAL_H
