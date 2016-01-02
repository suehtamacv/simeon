#ifndef LINEAMPLIFIER_H
#define LINEAMPLIFIER_H

#include <Devices/Amplifiers/EDFA.h>

class Fiber;

/**
 * @brief The InLineAmplifier class represents an In-Line Amplifier.
 *
 * Those amplifiers are scattered through the fiber. Each amplifier compensates
 * for the loss in the precedent fiber segment.
 */
class InLineAmplifier : public EDFA {
  public:
    /**
     * @brief AT is the type of amplifier.
     */
    static constexpr AmplifierType AT = Amplifier::InLineAmplifierType;
    /**
     * @brief InLineAmplifier is the standard constructor for a InLineAmplifier.
     * @param Segment is a pointer to the precedent Fiber segment. This amplifier
     * will compensate for the loss in such segment.
     */
    InLineAmplifier(Fiber &Segment);

    Gain &get_Gain();

    std::shared_ptr<Device> clone();
};

#endif // LINEAMPLIFIER_H
