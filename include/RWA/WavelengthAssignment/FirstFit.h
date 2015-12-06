#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include <RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.h>

class FirstFit : public WavelengthAssignmentAlgorithm {
  public:
    FirstFit(std::shared_ptr<Topology> T);

    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>>
    assignSlots(Call C, std::vector<std::weak_ptr<Link>> Links);
};

#endif // FIRSTFIT_H
