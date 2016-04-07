#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include <RMSA/SpectrumAssignmentAlgorithms/SpectrumAssignmentAlgorithm.h>

namespace RMSA
{
namespace SA
{
/**
 * @brief The FirstFit class represents the First Fit spectrum assignment algorithm.
 * It tries to allocate the requisition on the first block of slots that are capable
 * of containing the requisition.
 */
class FirstFit : public SpectrumAssignmentAlgorithm
{
public:
    FirstFit(std::shared_ptr<Topology> T);

    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};
}
}

#endif // FIRSTFIT_H
