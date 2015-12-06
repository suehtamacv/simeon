#ifndef NODALDEGREEFIRST_H
#define NODALDEGREEFIRST_H

#include <RWA/RegeneratorPlacement/NX_RegeneratorPlacement.h>

class NodalDegreeFirst : public NX_RegeneratorPlacement {
  public:
    NodalDegreeFirst(std::shared_ptr<Topology> T);
    void placeRegenerators(int N, int X);
};

#endif // NODALDEGREEFIRST_H
