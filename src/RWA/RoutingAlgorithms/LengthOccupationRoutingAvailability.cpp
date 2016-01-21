#include <RWA/RoutingAlgorithms/LengthOccupationRoutingAvailability.h>
#include <Structure/Link.h>
#include <Structure/Topology.h>

LengthOccupationRoutingAvailability::LengthOccupationRoutingAvailability(
    std::shared_ptr<Topology> T) : DijkstraRoutingAlgorithm(T)
{

}

double LengthOccupationRoutingAvailability::get_Cost(
    std::weak_ptr<Link> link,
    std::shared_ptr<Call>)
{
    return 1 + (link.lock()->Length / T->get_LengthLongestLink());
}
