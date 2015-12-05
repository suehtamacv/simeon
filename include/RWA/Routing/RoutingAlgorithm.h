#ifndef ROUTINGALGORITHM_H
#define ROUTINGALGORITHM_H

#include <memory>
#include <vector>
#include <Calls/Call.h>
#include <Structure/Topology.h>

class RoutingAlgorithm {
  public:
    RoutingAlgorithm(std::shared_ptr<Topology> T);

    virtual std::vector<std::weak_ptr<Link>> route(Call C) = 0;

    std::shared_ptr<Topology> T;
};

#endif // ROUTINGALGORITHM_H
