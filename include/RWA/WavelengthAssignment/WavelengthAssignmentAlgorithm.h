#ifndef WAVELENGTHASSIGNMENTALGORITHM_H
#define WAVELENGTHASSIGNMENTALGORITHM_H

#include <map>
#include <Calls/Call.h>
#include <Structure/Slot.h>
#include <Structure/Topology.h>

class WavelengthAssignmentAlgorithm {
  public:
    WavelengthAssignmentAlgorithm(std::shared_ptr<Topology> T);

    virtual std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>>
    assignSlots(Call C, std::vector<std::weak_ptr<Link>> Links) = 0;

    std::shared_ptr<Topology> T;
};

#endif // WAVELENGTHASSIGNMENTALGORITHM_H
