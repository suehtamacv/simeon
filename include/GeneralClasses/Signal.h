#ifndef SIGNAL_H
#define SIGNAL_H

#include <GeneralClasses/Power.h>
#include <GeneralClasses/SpectralDensity.h>
#include <vector>
#include <memory>

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
     * @brief get_OSNR returns the Signal-To-Noise Ratio of the Signal.
     * @return the Signal-To-Noise Ratio of the Signal.
     */
    Gain get_OSNR();
    /**
     * @brief get_NoisePower returns the Noise Power of the Signal.
     * @return the Noise Power of the Signal.
     */
    Power get_NoisePower();

    static unsigned long  numSamples;

    std::shared_ptr<SpectralDensity> signalSpecDensity;

private:
    Power SignalPower;
    Power NoisePower;
};

#endif // SIGNAL_H
