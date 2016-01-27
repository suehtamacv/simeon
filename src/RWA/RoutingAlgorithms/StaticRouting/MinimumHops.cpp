#include <RWA/RoutingAlgorithms/StaticRouting/MinimumHops.h>

MinimumHops::MinimumHops(std::shared_ptr<Topology> T) :
    StaticRoutingAlgorithm(T, MH)
{

}

double MinimumHops::get_Cost(
    std::weak_ptr<Link>,
    std::shared_ptr<Call>)
{
    return 1;
}

void MinimumHops::save(std::string SimConfigFileName)
{
    RoutingAlgorithm::save(SimConfigFileName);
}
