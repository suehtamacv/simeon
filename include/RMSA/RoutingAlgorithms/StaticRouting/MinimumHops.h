#ifndef MINIMUMHOPS_H
#define MINIMUMHOPS_H

#include <RMSA/RoutingAlgorithms/StaticRouting/FixedRoutingAlgorithm.h>

namespace ROUT
{
/**
 * @brief The MinimumHops class represents the Minimum Hops routing algorithm.
 * The link cost of each link is 1.
 */
class MinimumHops : public FixedRoutingAlgorithm
{
public:
    MinimumHops(std::shared_ptr<Topology> T);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call>);
    void load() {}
    void save(std::string);
};
}

#endif // MINIMUMHOPS_H
