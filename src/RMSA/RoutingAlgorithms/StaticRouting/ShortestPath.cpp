#include <RMSA/RoutingAlgorithms/StaticRouting/ShortestPath.h>
#include <Structure/Link.h>

using namespace RMSA::ROUT;

ShortestPath::ShortestPath(std::shared_ptr<Topology> T) :
    FixedRoutingCost(T, SP)
{

}

double ShortestPath::get_Cost(
    std::weak_ptr<Link> link,
    std::shared_ptr<Call>)
{
    if (!link.lock()->is_LinkActive())
        {
        return std::numeric_limits<double>::max();
        }

    return link.lock()->Length;
}

void ShortestPath::save(std::string SimConfigFileName)
{
    RoutingCost::save(SimConfigFileName);
}
