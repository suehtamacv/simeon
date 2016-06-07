#ifndef LEASTUSED_H
#define LEASTUSED_H

#include "SpectrumAssignmentAlgorithm.h"

namespace RMSA
{
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

    mapSlots assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};
}
}

#endif // LEASTUSED_H
