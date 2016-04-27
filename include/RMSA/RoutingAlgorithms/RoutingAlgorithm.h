#ifndef ROUTINGALGORITHM_H
#define ROUTINGALGORITHM_H

#include <boost/bimap.hpp>
#include <memory>
#include <vector>

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
    X(bellman_ford, "Bellman-Ford Shortest Path Algorithm", "bellman_ford") \
    X(dijkstra_alg, "Dijkstra Shortest Path Algorithm", "dijkstra_alg") \
    X(yen_alg, "Yen K-Shortest Path Algorithm", "yen_alg")

#define X(a,b,c) a,
    enum RoutingAlgorithms
    {
        ROUTING_ALGORITHM
    };
#undef X

    typedef boost::bimap<RoutingAlgorithms, std::string> RoutTypeNameBimap;
    static RoutTypeNameBimap RoutingTypesNames;
    typedef boost::bimap<RoutingAlgorithms, std::string> RoutTypeNicknameBimap;
    static RoutTypeNicknameBimap RoutingTypesNicknames;

    static RoutingAlgorithms RoutType;

    RoutingAlgorithm(std::shared_ptr<Topology> T, RoutingAlgorithms RoutType);

    static RoutingAlgorithms define_RoutingAlgorithm();
    static std::shared_ptr<RoutingAlgorithm> create_RoutingAlgorithm(
        RoutingAlgorithms, std::shared_ptr<Topology>);
    virtual void load() = 0;
    virtual void save(std::string) = 0;

    virtual std::vector<std::vector<std::weak_ptr<Link>>>
    route(std::shared_ptr<Call> C) = 0;

    std::shared_ptr<Topology> T;

    /**
     * @brief kShortestPaths is the number of shortest paths that will be searched
     * by the KSP Algorithms, like Yen on Eppstein,  if one of them is choosed.
     */
    static constexpr int kShortestPaths = 3;

private:
    std::vector<std::vector<std::weak_ptr<Link>>> bell_ford(
        std::shared_ptr<Call> C);
    std::vector<std::vector<std::weak_ptr<Link>>> dijkstra(std::shared_ptr<Call> C);
    std::vector<std::vector<std::weak_ptr<Link>>> yen(std::shared_ptr<Call> C);
    static bool hasLoadedRoutingType;

    double get_RoutingCost(std::vector<std::weak_ptr<Link>>, std::shared_ptr<Call>);
};
}
}

#endif // ROUTINGALGORITHM_H
