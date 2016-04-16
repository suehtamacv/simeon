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
    return 1.0 + link.lock()->Length / T->get_LengthLongestLink() -
           link.lock()->get_Availability() / (double) Link::NumSlots;
}

void LengthOccupationRoutingAvailability::save(std::string SimConfigFileName)
{
    RoutingAlgorithm::save(SimConfigFileName);
}
