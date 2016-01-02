#include <RWA/RoutingAlgorithms/StaticRouting/ShortestPath.h>
#include <Structure/Link.h>

ShortestPath::ShortestPath(std::shared_ptr<Topology> T) :
    StaticRoutingAlgorithm(T) {

}

double ShortestPath::get_Cost(
    std::weak_ptr<Link> link,
    std::shared_ptr<Call>) {
    return link.lock()->Length;
}
