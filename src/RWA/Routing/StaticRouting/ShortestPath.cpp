#include <RWA/Routing/StaticRouting/ShortestPath.h>

ShortestPath::ShortestPath(std::shared_ptr<Topology> T) :
    StaticRoutingAlgorithm(T) {

}

long double ShortestPath::get_Cost(std::weak_ptr<Link> Link, Call) {
    return Link.lock()->Length;
}

