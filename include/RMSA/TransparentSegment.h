#ifndef TRANSPARENTSEGMENT_H
#define TRANSPARENTSEGMENT_H

#include <memory>
#include <vector>
#include <map>
#include <GeneralClasses/Signal.h>
#include <GeneralClasses/ModulationScheme.h>
#include <GeneralClasses/Power.h>

class Link;
class Node;
class Slot;
class Call;

namespace RMSA
{
/**
 * @brief The TransparentSegment class is a set of links, into which a call is
 * implemented.
 *
 * The call is implemented using contigue slots through all the links, and using
 * a single modulation scheme. Optional regenerators can be used at the final node.
 */
class TransparentSegment
{
public:
    /**
     * @brief TransparentSegment is the standard constructor for a
     * TransparentSegment.
     * @param Links is a vector of pointers to the links that compose the
     * TransparentSegment.
     * @param ModScheme is the modulation scheme used to implement the Segment.
     * @param NumRegUsed is the number of regenerators used in the final node
     * of the segment. It defaults to zero. A non zero value requires that the
     * final node is translucent, that is, has regenerators.
     */
    TransparentSegment(std::vector<std::weak_ptr<Link>> Links,
                       ModulationScheme ModScheme,
                       unsigned int NumRegUsed = 0);
    /**
     * @brief TransparentSegment is the copy constructor for a TransparentSegment.
     * @param segment is a pointer to another segment.
     */
    TransparentSegment(const TransparentSegment &segment);

    /**
     * @brief Nodes is a vector with the nodes in the TransparentSegment.
     */
    std::vector<std::weak_ptr<Node>> Nodes;
    /**
     * @brief Links is a vector with the links in the TransparentSegment.
     */
    std::vector<std::weak_ptr<Link>> Links;
    /**
     * @brief ModScheme is the ModulationScheme used to implement the call on the
     * TransparentSegment.
     */
    ModulationScheme ModScheme;
    /**
     * @brief NumRegUsed is the number of regenerators used on the last node
     * of the transparent segment.
     */
    unsigned int NumRegUsed;

    /**
     * @brief bypass is used to analyze the signal quality after it has traversed
     * the transparent segment.
     * @param S is the input signal.
     * @return the Signal after it has traversed the network.
     */
    Signal bypass(Signal S);
    /**
     * @brief get_MaxContigSlots returns the maximum number of adjacent free slots
     * in the TransparentSegment.
     * @return the maximum number of adjacent free slots in the TransparentSegment.
     */
    unsigned int get_MaxContigSlots();
    /**
     * @brief get_Contiguity returns the contiguity measure of this segment. This
     * measure is how many ways it is possible to allocate the required slots by
     * Call C on this segment.
     * @param C is the Call against whom the contiguity measured is calculated.
     * @return in how many ways it is possible to allocate the required slots by
     * Call C on this segment.
     */
    int get_Contiguity(std::shared_ptr<Call> C);
    /**
     * @brief TransmissionPower is the power of the transmited singal.
     */
    Power transmitedPower;

    std::vector<SpectralDensity> opticalPathSpecDensity;
};
}

#endif // TRANSPARENTSEGMENT_H
