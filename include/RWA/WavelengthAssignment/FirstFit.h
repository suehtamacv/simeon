#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include <RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.h>

class FirstFit : public WavelengthAssignmentAlgorithm {
  public:
    FirstFit(std::shared_ptr<Topology> T, std::vector<ModulationScheme> Schemes);

    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(Call C, TransparentSegment Seg);
};

#endif // FIRSTFIT_H
