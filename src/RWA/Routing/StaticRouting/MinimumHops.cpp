#include <RWA/Routing/StaticRouting/MinimumHops.h>

MinimumHops::MinimumHops(std::shared_ptr<Topology> T) :
    StaticRoutingAlgorithm(T) {

}

long double MinimumHops::get_Cost(std::weak_ptr<Link>, Call) {
    return 1;
}
