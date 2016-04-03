#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <RMSA/RoutingAlgorithms/StaticRouting/FixedRoutingAlgorithm.h>

namespace ROUT
{
/**
 * @brief The ShortestPath class represents the Shortest Path routing algorithm.
 * The link cost of each link is its length.
 */
class ShortestPath : public FixedRoutingAlgorithm
{
public:
    ShortestPath(std::shared_ptr<Topology> T);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call>);
    void load() {}
    void save(std::string);
};
}

#endif // SHORTESTPATH_H
