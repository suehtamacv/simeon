#include <RMSA/RoutingAlgorithms/LengthOccupationRoutingAvailability.h>
#include <Structure/Link.h>
#include <Structure/Topology.h>

using namespace RMSA::ROUT;

LengthOccupationRoutingAvailability::LengthOccupationRoutingAvailability(
    std::shared_ptr<Topology> T) :
    RoutingAlgorithm(T, LORa)
{

}

double LengthOccupationRoutingAvailability::get_Cost(
    std::weak_ptr<Link> link,
    std::shared_ptr<Call>)
{
    if (!link.lock()->is_LinkActive())
        {
        return std::numeric_limits<double>::max();
        }

    return 1.0 + link.lock()->Length / T->get_LengthLongestLink() -
           link.lock()->get_Availability() / (double) Link::NumSlots;
}

void LengthOccupationRoutingAvailability::save(std::string SimConfigFileName)
{
    RoutingAlgorithm::save(SimConfigFileName);
}

std::vector<std::vector<std::weak_ptr<Link>>>
LengthOccupationRoutingAvailability::route(std::shared_ptr<Call> C)
{
    return RoutingAlgorithm::route(C);
}
