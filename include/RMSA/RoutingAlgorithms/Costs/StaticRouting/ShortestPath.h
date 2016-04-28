#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <RMSA/RoutingAlgorithms/Costs/StaticRouting/FixedRoutingCost.h>

namespace RMSA
{
namespace ROUT
{
/**
 * @brief The ShortestPath class represents the Shortest Path routing algorithm.
 * The link cost of each link is its length.
 */
class ShortestPath : public FixedRoutingCost
{
public:
    ShortestPath(std::shared_ptr<Topology> T);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call>);
    void load()
    {
        RoutingCost::load();
    }
    void save(std::string);
};
}
}

#endif // SHORTESTPATH_H
