#ifndef EXACTFIT_H
#define EXACTFIT_H

#include "SpectrumAssignmentAlgorithm.h"

namespace SA
{
/**
 * @brief The ExactFit class represents the Exact Fit spectrum assignment algorithm.
 * It tries to allocate the requisition of N slots on a block with exactly N slots. If
 * such block doesn't exist, then it calls FirstFit.
 */
class ExactFit : public SpectrumAssignmentAlgorithm
{
public:
    /**
     * @brief ExactFit is the standard constructor to the Exact Fit SA algorithm.
     * @param T is the Topology.
     */
    ExactFit(std::shared_ptr<Topology> T);

    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};
}
#endif // EXACTFIT_H
