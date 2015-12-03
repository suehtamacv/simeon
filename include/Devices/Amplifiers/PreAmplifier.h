#ifndef PREAMPLIFIER_H
#define PREAMPLIFIER_H

#include <Devices/Amplifiers/Amplifier.h>

class Node;
class Fiber;

class PreAmplifier : public Amplifier {
  public:
    static constexpr AmplifierType AT = Amplifier::PreAmplifierType;
    /**
     * @brief PreAmplifier is the standard constructor for a pre-amplifier
     * @param G is the Gain of the Amplifier
     * @param numPorts
     */
    PreAmplifier(Fiber &Segment, Node &Node);

    Gain get_Gain();
  private:
    unsigned numPorts;
    Node &Destination;
};

#endif // PREAMPLIFIER_H
