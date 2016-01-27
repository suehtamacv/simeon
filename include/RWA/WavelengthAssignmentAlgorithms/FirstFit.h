#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include <RWA/WavelengthAssignmentAlgorithms/WavelengthAssignmentAlgorithm.h>

class FirstFit : public WavelengthAssignmentAlgorithm
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

#endif // FIRSTFIT_H
