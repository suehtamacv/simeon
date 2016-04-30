#ifndef YEN_ROUTINGALGORITHM_H
#define YEN_ROUTINGALGORITHM_H

#include "../RoutingAlgorithm.h"
#include "include/RMSA/RoutingAlgorithms/Algorithms/Dijkstra_RoutingAlgorithm.h"

namespace RMSA
{
namespace ROUT
{
class Yen_RoutingAlgorithm : public RoutingAlgorithm
{
public:
    Yen_RoutingAlgorithm(std::shared_ptr<Topology> T,
                         RoutingCost::RoutingCosts Cost,
                         bool runLoad);
    std::vector<std::vector<std::weak_ptr<Link>>> route(std::shared_ptr<Call> C);

    void load();
    void save(std::string);

    /**
     * @brief kShortestPaths is the number of shortest paths that will be searched
     * by the KSP Algorithms, like Yen on Eppstein,  if one of them is choosed.
     */
    static unsigned int kShortestPaths;
    static bool hasLoaded;

private:
    std::shared_ptr<RoutingAlgorithm> Dijkstra;
};
}
}

#endif // YEN_ROUTINGALGORITHM_H
