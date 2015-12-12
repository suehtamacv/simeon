#include <RWA/Routing/LengthOccupationRoutingContiguity.h>
#include <Structure/Link.h>

LengthOccupationRoutingContiguity::LengthOccupationRoutingContiguity(
    std::shared_ptr<Topology> T) : DijkstraRoutingAlgorithm(T) {

}

long double LengthOccupationRoutingContiguity::get_Cost(
    std::weak_ptr<Link> link, std::shared_ptr<Call> C) {
    return 1 +
           (link.lock()->Length / T->get_LengthLongestLink()) +
           (1.0 / (link.lock()->get_Contiguity(C) + 1));
}
