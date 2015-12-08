#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include <RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.h>

class FirstFit : public WavelengthAssignmentAlgorithm {
  public:
    FirstFit(std::shared_ptr<Topology> T);
};

#endif // FIRSTFIT_H
