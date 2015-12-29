#include <RWA/RoutingAlgorithms/LengthOccupationRoutingContiguity.h>
#include <Structure/Link.h>
#include <Structure/Topology.h>

LengthOccupationRoutingContiguity::LengthOccupationRoutingContiguity(
    std::shared_ptr<Topology> T) : DijkstraRoutingAlgorithm(T) {

}

double LengthOccupationRoutingContiguity::get_Cost(
    std::weak_ptr<Link> link,
    std::shared_ptr<Call> C) {
    return 1 +
           (link.lock()->Length / T->get_LengthLongestLink()) +
           (1.0 / (link.lock()->get_Contiguity(C) + 1));
}
