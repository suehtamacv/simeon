#ifndef STATICROUTINGALGORITHM_H
#define STATICROUTINGALGORITHM_H

#include <RWA/Routing/RoutingAlgorithm.h>

/**
 * @brief The StaticRoutingAlgorithm class is a class of routing algorithms
 * whose routes only depend on the origin and destination of the call, remaining
 * constant through the whole simulation.
 */
class StaticRoutingAlgorithm : public RoutingAlgorithm {
  public:
    StaticRoutingAlgorithm(std::shared_ptr<Topology> T);
};

#endif // STATICROUTINGALGORITHM_H
