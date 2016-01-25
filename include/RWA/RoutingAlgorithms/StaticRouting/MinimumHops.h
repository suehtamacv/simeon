#ifndef MINIMUMHOPS_H
#define MINIMUMHOPS_H

#include <RWA/RoutingAlgorithms/StaticRouting/StaticRoutingAlgorithm.h>

class MinimumHops : public StaticRoutingAlgorithm
{
public:
    MinimumHops(std::shared_ptr<Topology> T);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call>);
    void load() {}
    void save(std::string);
};

#endif // MINIMUMHOPS_H
