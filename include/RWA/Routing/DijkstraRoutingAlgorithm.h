#ifndef DIJKSTRAROUTINGALGORITHM_H
#define DIJKSTRAROUTINGALGORITHM_H

#include <RWA/Routing/RoutingAlgorithm.h>

/**
 * @brief The DijkstraRoutingAlgorithm class is a class of routing algorithms
 * whose routes are determined using the Dijkstra Shortest Path algorithm.
 */
class DijkstraRoutingAlgorithm : public RoutingAlgorithm {
  public:
    DijkstraRoutingAlgorithm(std::shared_ptr<Topology> T);

    std::vector<std::weak_ptr<Link>> route(std::shared_ptr<Call> C);
    virtual long double get_Cost(std::weak_ptr<Link> Link, std::shared_ptr<Call> C) = 0;
};

#endif // DIJKSTRAROUTINGALGORITHM_H
