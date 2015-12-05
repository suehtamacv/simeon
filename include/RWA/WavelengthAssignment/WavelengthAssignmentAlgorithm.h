#ifndef WAVELENGTHASSIGNMENTALGORITHM_H
#define WAVELENGTHASSIGNMENTALGORITHM_H

#include <Calls/Call.h>
#include <Structure/Topology.h>

class WavelengthAssignmentAlgorithm {
  public:
    WavelengthAssignmentAlgorithm(std::shared_ptr<Topology> T);

    std::shared_ptr<Topology> T;
};

#endif // WAVELENGTHASSIGNMENTALGORITHM_H
