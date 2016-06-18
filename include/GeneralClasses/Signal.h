#ifndef SIGNAL_H
#define SIGNAL_H

#include <GeneralClasses/Power.h>
#include <GeneralClasses/SpectralDensity.h>
#include <Structure/Slot.h>
#include <vector>
#include <memory>
#include <map>

extern bool considerAseNoise;
extern bool considerFilterImperfection;

typedef std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>, std::owner_less<std::weak_ptr<Link>>>
        mapSlots;

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
    Signal(mapSlots);
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
    Signal &operator *=(std::shared_ptr<TF::Transmittance>);
    /**
     * @brief operator += adds a crosstalk PSD to this signal's crosstalk.
     * @return a signal after adding the crosstalk.
     */
    Signal &operator +=(SpectralDensity &);
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
     * @brief get_WeightedCrosstalk returns the weighted crosstalk interfering with this signal.
     * @return the weighted crosstalk interfering with this signal.
     */
    Gain get_WeightedCrosstalk();
    /**
     * @brief get_SignalPowerRatio returns the ratio of this signal's original and final spectral density power.
     * @return the ratio of this signal's original and final spectral density power.
     */
    Gain get_SignalPowerRatio();
    /**
     * @brief numSlots is the number of slots occupied by this Signal.
     */
    unsigned int numSlots;
    /**
     * @brief freqMin is the minimum frequency occupied by this Signal.
     */
    double freqMin;
    /**
     * @brief freqMax is the maximum frequency occupied by this Signal.
     */
    double freqMax;

    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> occupiedSlots;
    /**
     * @brief signalSpecDensity is the signal's spectral density.
     */
    std::shared_ptr<SpectralDensity> signalSpecDensity;
    /**
     * @brief incomingLink is the last link that this signal crossed
     */
    std::weak_ptr<Link> incomingLink;

private:

    Power SignalPower;
    Power NoisePower;
    /**
     * @brief originalSpecDensityCache is a map with the spectral density power of a signal, given a number of slots.
     */
    std::map<int, Power> originalSpecDensityCache ;
    /**
     * @brief crosstalkSpecDensity is this signal's crosstalk interference.
     */
    std::shared_ptr<SpectralDensity> crosstalkSpecDensity;
};

#endif // SIGNAL_H
