#ifndef REGENERATORPLACEMENTALGORITHM_H
#define REGENERATORPLACEMENTALGORITHM_H

#include <Structure/Topology.h>

class RegeneratorPlacementAlgorithm {
  public:
    RegeneratorPlacementAlgorithm(std::shared_ptr<Topology> T);
    std::shared_ptr<Topology> T;
    virtual void placeRegenerators(unsigned, unsigned) = 0;
};

#endif // REGENERATORPLACEMENTALGORITHM_H
