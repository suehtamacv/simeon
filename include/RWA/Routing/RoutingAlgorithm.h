#ifndef ROUTINGALGORITHM_H
#define ROUTINGALGORITHM_H

#include <Calls/Call.h>
#include <Structure/Topology.h>

class RoutingAlgorithm {
  public:
    RoutingAlgorithm(std::shared_ptr<Topology> T);

    std::shared_ptr<Topology> T;
};

#endif // ROUTINGALGORITHM_H
