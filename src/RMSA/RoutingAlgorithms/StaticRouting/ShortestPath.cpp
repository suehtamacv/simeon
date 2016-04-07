#include <RMSA/RoutingAlgorithms/StaticRouting/ShortestPath.h>
#include <Structure/Link.h>

using namespace RMSA::ROUT;

ShortestPath::ShortestPath(std::shared_ptr<Topology> T) :
    FixedRoutingAlgorithm(T, SP)
{

}

double ShortestPath::get_Cost(
    std::weak_ptr<Link> link,
    std::shared_ptr<Call>)
{
    return link.lock()->Length;
}

void ShortestPath::save(std::string SimConfigFileName)
{
    RoutingAlgorithm::save(SimConfigFileName);
}
