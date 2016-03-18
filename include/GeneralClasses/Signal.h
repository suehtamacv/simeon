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

    Power get_SpectralPower();

    double get_SignalPowerRatio(int numLinks); // Adicionei esse parâmetro para testes

    double get_PowerRatioThreshold();

    static unsigned long  numFrequencySamples;

    unsigned int numSlots;

private:
    Power SignalPower;
    Power NoisePower;
    double frequencyRange;

    std::map<int, Power> originalSpecDensityCache ;
    std::shared_ptr<SpectralDensity> signalSpecDensity;

};

#endif // SIGNAL_H
