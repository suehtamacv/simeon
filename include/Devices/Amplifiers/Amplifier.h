#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include <Devices/Device.h>

/**
 * @brief The Amplifier class represents an amplifier, that amplifies a signal
 * and generates noise.
 */
class Amplifier : public Device {
  public:
    /**
     * @brief The AmplifierType enum is used to identify the type of amplifier.
     */
    enum AmplifierType {
        InLineAmplifierType, /*!< In-Line Amplifier */
        BoosterAmplifierType, /*!< Booster Amplifier */
        PreAmplifierType /*!< Pre-Amplifier */
    };

    /**
     * @brief Amplifier is the standard constructor for a Amplifier.
     * @param G is the Gain of the amplifier.
     */
    Amplifier(Gain G);

    Power &get_Noise();
    double get_CapEx();
    double get_OpEx();

    /**
     * @brief set_Gain is used to set a new gain of this Amplifier.
     * @param G is the new gain of this Amplifier.
     */
    void set_Gain(Gain G);

    /**
     * @brief AmplifierGain is the gain of this amplifier.
     */
    Gain AmplifierGain;
    /**
     * @brief NoisePower is the power of the ASE noise generated by the amplifier.
     */
    Power NoisePower;

  private:
    /**
     * @brief calculate_NoisePower calculates the ASE Noise power
     * generated by the amplifier.
     */
    virtual void calculate_NoisePower() = 0;

};

#endif // AMPLIFIER_H
