#include <RMSA/RoutingAlgorithms/Costs/LengthOccupationRoutingContiguity.h>
#include <Structure/Link.h>
#include <Structure/Topology.h>

using namespace RMSA::ROUT;

LengthOccupationRoutingContiguity::LengthOccupationRoutingContiguity(
    std::shared_ptr<Topology> T) : RoutingCost(T, LORc)
{

}

double LengthOccupationRoutingContiguity::get_Cost(
    std::weak_ptr<Link> link,
    std::shared_ptr<Call> C)
{
    if (!link.lock()->is_LinkActive())
        {
        return std::numeric_limits<double>::max();
        }

    return 1 +
           (link.lock()->Length / T->get_LengthLongestLink()) +
           (1.0 / (link.lock()->get_Contiguity(C) + 1));
}

void LengthOccupationRoutingContiguity::save(std::string SimConfigFileName)
{
    RoutingCost::save(SimConfigFileName);
}
