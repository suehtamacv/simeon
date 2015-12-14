#ifndef NODALDEGREEFIRST_H
#define NODALDEGREEFIRST_H

#include <RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>

class NodalDegreeFirst : public NX_RegeneratorPlacement {
  public:
    NodalDegreeFirst(std::shared_ptr<Topology> T);
    void placeRegenerators(unsigned N, unsigned X);
};

#endif // NODALDEGREEFIRST_H
