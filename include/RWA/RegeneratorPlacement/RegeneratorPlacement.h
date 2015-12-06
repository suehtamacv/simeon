#ifndef REGENERATORPLACEMENT_H
#define REGENERATORPLACEMENT_H

#include <Structure/Topology.h>

class RegeneratorPlacement {
  public:
    RegeneratorPlacement(std::shared_ptr<Topology> T);

    std::shared_ptr<Topology> T;

  private:
    virtual void placeRegenerators(int, int) = 0;
};

#endif // REGENERATORPLACEMENT_H
