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
    static constexpr AmplifierType AT = Amplifier::InLineAmplifierType;
    InLineAmplifier(Fiber &Segment);

    Gain get_Gain();
    std::shared_ptr<Device> clone();
};

#endif // LINEAMPLIFIER_H
