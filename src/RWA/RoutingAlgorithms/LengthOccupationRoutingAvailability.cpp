#include <RWA/RoutingAlgorithms/LengthOccupationRoutingAvailability.h>
#include <Structure/Link.h>

LengthOccupationRoutingAvailability::LengthOccupationRoutingAvailability(
    std::shared_ptr<Topology> T) : DijkstraRoutingAlgorithm(T) {

}

long double LengthOccupationRoutingAvailability::get_Cost(
    std::weak_ptr<Link> link, std::shared_ptr<Call>) {
    return 1 +
           (link.lock()->Length / T->get_LengthLongestLink()) +
           (link.lock()->get_Availability() / (long double) Link::NumSlots);
}
