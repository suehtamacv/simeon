#ifndef CONTIGUITYFIT_H
#define CONTIGUITYFIT_H

#include "SpectrumAssignmentAlgorithm.h"

namespace RMSA
{
namespace SA
{
/**
 * @brief The BestFit class represents the Best Fit spectrum assignment algorithm.
 * It will allocate the requisition on the smallest possible block that can contain
 * the requisition.
 */
class BestFit : public SpectrumAssignmentAlgorithm
{
public:
    /**
     * @brief BestFit is the standard constructor to the Best Fit SA algorithm.
     * @param T is the Topology.
     */
    BestFit(std::shared_ptr<Topology> T);

    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};
}
}

#endif // CONTIGUITYFIT_H
