#ifndef PREAMPLIFIER_H
#define PREAMPLIFIER_H

#include <Devices/Amplifiers/EDFA.h>

class Node;
class Fiber;

/**
 * @brief The PreAmplifier class represents a Pre-Amplifier.
 *
 * In the current architecture such amplifier is on the node's entrance. It
 * compensates for the loss in the precedent fiber segment and for the loss in
 * the succedent switching element (either a SSS or a Splitter).
 */
class PreAmplifier : public EDFA
{
public:
    /**
     * @brief AT is the type of amplifier.
     */
    static constexpr AmplifierType AT = Amplifier::PreAmplifierType;
    /**
     * @brief PreAmplifier is the standard constructor for a pre-amplifier
     * @param Segment is the precedent fiber segment.
     * @param Node is the owner Node of this PreAmplifier.
     */
    PreAmplifier(Fiber &Segment, Node &Node);

    Gain &get_Gain();
    std::shared_ptr<Device> clone();

private:
    unsigned numPorts;
    Node &Destination;
    Fiber &Segment;
};

#endif // PREAMPLIFIER_H
