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

    mapSlots assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};
}
}

#endif // MOSTUSED_H
