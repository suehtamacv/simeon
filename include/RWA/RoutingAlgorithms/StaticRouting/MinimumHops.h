#ifndef MINIMUMHOPS_H
#define MINIMUMHOPS_H

#include <RWA/RoutingAlgorithms/StaticRouting/StaticRoutingAlgorithm.h>

class MinimumHops : public StaticRoutingAlgorithm {
  public:
    MinimumHops(std::shared_ptr<Topology> T);

    long double get_Cost(std::weak_ptr<Link> Link, std::shared_ptr<Call>);
};

#endif // MINIMUMHOPS_H
