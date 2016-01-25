#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <RWA/RoutingAlgorithms/StaticRouting/StaticRoutingAlgorithm.h>

class ShortestPath : public StaticRoutingAlgorithm
{
public:
    ShortestPath(std::shared_ptr<Topology> T);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call>);
    void load() {}
    void save(std::string);
};

#endif // SHORTESTPATH_H
