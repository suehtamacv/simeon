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
    X(bellman_ford, "Bellman-Ford Shortest Path Algorithm", "bellman_ford", BellmanFord_RoutingAlgorithm) \
    X(dijkstra_alg, "Dijkstra Shortest Path Algorithm", "dijkstra_alg", Dijkstra_RoutingAlgorithm) \
    X(yen_alg, "Yen K-Shortest Path Algorithm", "yen_alg", Yen_RoutingAlgorithm)

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

    RoutingAlgorithm(std::shared_ptr<Topology> T, RoutingAlgorithms RoutAlg);
    RoutingAlgorithm(std::shared_ptr<Topology> T, RoutingAlgorithms RoutAlg,
                     RoutingCost::RoutingCosts RoutCost);

    static RoutingAlgorithms define_RoutingAlgorithm();
    static std::shared_ptr<RoutingAlgorithm> create_RoutingAlgorithm(
        RoutingAlgorithms, std::shared_ptr<Topology>);
    virtual void load() = 0;
    virtual void save(std::string) = 0;

    virtual std::vector<std::vector<std::weak_ptr<Link>>>
    route(std::shared_ptr<Call> C) = 0;

    std::shared_ptr<Topology> T;

    static void define_RoutingCost(RoutingCost::RoutingCosts Cost);
    static RoutingCost::RoutingCosts Cost;
    static RoutingAlgorithms Alg;

private:
    static bool hasLoadedRoutingCost;
    static bool hasLoadedRoutingAlg;

    double get_RoutingCost(std::vector<std::weak_ptr<Link>>, std::shared_ptr<Call>);
};
}
}

#endif // ROUTINGALGORITHM_H
