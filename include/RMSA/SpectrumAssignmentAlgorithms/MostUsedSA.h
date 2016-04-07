#ifndef MOSTUSED_H
#define MOSTUSED_H

#include "SpectrumAssignmentAlgorithm.h"

namespace RMSA
{
namespace SA
{
/**
 * @brief The MostUsed class represents the Most Used spectrum assignment algorithm.
 * It tries to allocate the requistion on the block of slots that are used the most
 * on the entire network.
 */
class MostUsed : public SpectrumAssignmentAlgorithm
{
public:
    /**
     * @brief MostUsed is the standard constructor for the Most Used SA algorithm
     * @param T is the Topology.
     */
    MostUsed(std::shared_ptr<Topology> T);

    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};
}
}

#endif // MOSTUSED_H
