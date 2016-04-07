#ifndef LEASTUSED_H
#define LEASTUSED_H

#include "SpectrumAssignmentAlgorithm.h"

namespace SA
{
/**
 * @brief The LeastUsed class represents the Least Used spectrum assignment algorithm.
 * It tries to allocate the requistion on the block of slots that are used the least
 * on the entire network.
 */
class LeastUsed : public SpectrumAssignmentAlgorithm
{
public:
    /**
     * @brief LeastUsed is the standard constructor for the Least Used SA algorithm
     * @param T is the Topology.
     */
    LeastUsed(std::shared_ptr<Topology> T);

    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};
}

#endif // LEASTUSED_H
