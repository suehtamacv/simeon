#ifndef RANDOMFIT_H
#define RANDOMFIT_H

#include "SpectrumAssignmentAlgorithm.h"

namespace RMSA
{
namespace SA
{
/**
 * @brief The RandomFit class represents the Random Fit spectrum assignment algorithm.
 * It tries to allocate the requisition on a block of slots randomly chosen.
 */
class RandomFit : public SpectrumAssignmentAlgorithm
{
public:
    /**
     * @brief RandomFit is the standard constructor for the Random Fit SA algorithm.
     * @param T is the topology.
     */
    RandomFit(std::shared_ptr<Topology> T);

    mapSlots assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};
}
}

#endif // RANDOMFIT_H
