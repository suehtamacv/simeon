#ifndef MOSTUSED_H
#define MOSTUSED_H

#include <RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>

class NetworkSimulation;

class MostUsed : public NX_RegeneratorPlacement {
  public:
    MostUsed(std::shared_ptr<Topology> T,
             std::shared_ptr<NetworkSimulation> Optimization);

    void placeRegenerators(unsigned N, unsigned X);

  private:
    std::shared_ptr<NetworkSimulation> Optimization;
};

#endif // MOSTUSED_H
