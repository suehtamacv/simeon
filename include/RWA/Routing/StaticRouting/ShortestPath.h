#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <RWA/Routing/StaticRouting/StaticRoutingAlgorithm.h>

class ShortestPath : public StaticRoutingAlgorithm {
  public:
    ShortestPath(std::shared_ptr<Topology> T);

    long double get_Cost(std::weak_ptr<Link> Link, Call);
};

#endif // SHORTESTPATH_H
