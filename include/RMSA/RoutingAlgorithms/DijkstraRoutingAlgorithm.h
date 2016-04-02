#ifndef DIJKSTRAROUTINGALGORITHM_H
#define DIJKSTRAROUTINGALGORITHM_H

#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>

/**
 * @brief The DijkstraRoutingAlgorithm class is a class of routing algorithms
 * whose routes are determined using the Dijkstra Shortest Path algorithm.
 */
class DijkstraRoutingAlgorithm : public RoutingAlgorithm
{
public:
    DijkstraRoutingAlgorithm(std::shared_ptr<Topology> T, RoutingAlgorithms RoutAlgType);

    std::vector<std::weak_ptr<Link>> route(std::shared_ptr<Call> C);
    virtual double get_Cost(std::weak_ptr<Link> link,
                            std::shared_ptr<Call> C) = 0;
};

#endif // DIJKSTRAROUTINGALGORITHM_H
