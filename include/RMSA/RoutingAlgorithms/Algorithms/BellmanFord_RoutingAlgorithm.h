#ifndef BELLMANFORD_ROUTINGALGORITHM_H
#define BELLMANFORD_ROUTINGALGORITHM_H

#include "../RoutingAlgorithm.h"

namespace RMSA
{
namespace ROUT
{
class BellmanFord_RoutingAlgorithm : public RoutingAlgorithm
{
public:
    BellmanFord_RoutingAlgorithm(std::shared_ptr<Topology> T,
                                 RoutingCost::RoutingCosts Cost,
                                 bool runLoad);
    std::vector<std::vector<std::weak_ptr<Link>>> route(std::shared_ptr<Call> C);

    void load() {}
    void save(std::string);
};
}
}

#endif // BELLMANFORD_ROUTINGALGORITHM_H
