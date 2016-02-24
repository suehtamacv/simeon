#ifndef EXACTFIT_H
#define EXACTFIT_H

#include "WavelengthAssignmentAlgorithm.h"

namespace WA
{
class ExactFit : public WavelengthAssignmentAlgorithm
{
public:
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
