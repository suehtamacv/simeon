#ifndef BOOSTERAMPLIFIER_H
#define BOOSTERAMPLIFIER_H

#include <Devices/Amplifiers/EDFA.h>

/**
 * @brief The BoosterAmplifier class represents a booster amplifier. In the
 * considered architecture it is on the node's exit.
 *
 * This amplifier compensates for the loss on the SSS device in the node's exit.
 */
class BoosterAmplifier : public EDFA
{
public:
    /**
     * @brief AT is the type of amplifier.
     */
    static constexpr AmplifierType AT = Amplifier::BoosterAmplifierType;
    /**
     * @brief BoosterAmplifier is the standard constructor for a BoosterAmplifier.
     */
    BoosterAmplifier();

    Gain &get_Gain();

    std::shared_ptr<Device> clone();
};

#endif // BOOSTERAMPLIFIER_H
