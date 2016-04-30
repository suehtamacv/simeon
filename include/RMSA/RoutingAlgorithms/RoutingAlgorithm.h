#ifndef ROUTINGALGORITHM_H
#define ROUTINGALGORITHM_H

#include <boost/bimap.hpp>
#include <memory>
#include <vector>
#include "RoutingCost.h"

class Topology;
class Call;
class Link;

namespace RMSA
{
//! Contains the routing algorithms
namespace ROUT
{
class RoutingCost;

/**
 * @brief The RoutingAlgorithm class searches for a route, given a Call.
 */
class RoutingAlgorithm
{
public:
#define ROUTING_ALGORITHM \
    X(bellmanford, "Bellman-Ford Shortest Path Algorithm", "bellmanford", BellmanFord_RoutingAlgorithm) \
    X(dijkstra, "Dijkstra Shortest Path Algorithm", "dijkstra", Dijkstra_RoutingAlgorithm) \
    X(yen, "Yen K-Shortest Path Algorithm", "yen", Yen_RoutingAlgorithm)

#define X(a,b,c,d) a,
    enum RoutingAlgorithms
    {
        ROUTING_ALGORITHM
    };
#undef X

    typedef boost::bimap<RoutingAlgorithms, std::string> RoutTypeNameBimap;
    static RoutTypeNameBimap RoutingAlgorithmNames;
    typedef boost::bimap<RoutingAlgorithms, std::string> RoutTypeNicknameBimap;
    static RoutTypeNicknameBimap RoutingAlgorithmNicknames;

    RoutingAlgorithms RoutAlg;
    std::shared_ptr<RoutingCost> RCost;

    RoutingAlgorithm(std::shared_ptr<Topology> T, RoutingAlgorithms RoutAlg,
                     RoutingCost::RoutingCosts RoutCost, bool runLoad = true);

    static RoutingAlgorithms define_RoutingAlgorithm();
    static std::shared_ptr<RoutingAlgorithm> create_RoutingAlgorithm(
        RoutingAlgorithms, RoutingCost::RoutingCosts, std::shared_ptr<Topology>,
            bool runLoad = true);
    virtual void load() = 0;
    virtual void save(std::string) = 0;

    virtual std::vector<std::vector<std::weak_ptr<Link>>>
    route(std::shared_ptr<Call> C) = 0;

    std::shared_ptr<Topology> T;

    RoutingCost::RoutingCosts Cost;
    RoutingAlgorithms Alg;

protected:
    double get_RoutingCost(std::vector<std::weak_ptr<Link>>, std::shared_ptr<Call>);
};
}
}

#endif // ROUTINGALGORITHM_H
