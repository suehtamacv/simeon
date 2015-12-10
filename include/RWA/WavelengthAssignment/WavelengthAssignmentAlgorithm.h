#ifndef WAVELENGTHASSIGNMENTALGORITHM_H
#define WAVELENGTHASSIGNMENTALGORITHM_H

#include <map>
#include <Calls/Call.h>
#include <Structure/Slot.h>
#include <Structure/Topology.h>
#include <RWA/TransparentSegment.h>

class WavelengthAssignmentAlgorithm {
  public:
    WavelengthAssignmentAlgorithm(std::shared_ptr<Topology> T);

    virtual std::map<std::weak_ptr<Link>,
            std::vector<std::weak_ptr<Slot>>,
            std::owner_less<std::weak_ptr<Link>>>
            assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg) = 0;

    std::shared_ptr<Topology> T;
};

#endif // WAVELENGTHASSIGNMENTALGORITHM_H
