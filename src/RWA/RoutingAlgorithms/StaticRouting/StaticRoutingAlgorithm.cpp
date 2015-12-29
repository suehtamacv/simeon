#include <RWA/RoutingAlgorithms/StaticRouting/StaticRoutingAlgorithm.h>

StaticRoutingAlgorithm::StaticRoutingAlgorithm(std::shared_ptr<Topology> T) :
    DijkstraRoutingAlgorithm(T) {
}

std::vector<std::weak_ptr<Link>> StaticRoutingAlgorithm::route(
std::shared_ptr<Call> C) {
    if (Routes.empty()) {
        precalculate_Routes();
    }

    OrigDestPair OrigDest(C->Origin.lock()->ID, C->Destination.lock()->ID);
    return Routes[OrigDest];
}

void StaticRoutingAlgorithm::precalculate_Routes() {
    for (auto &orig : T->Nodes) {
        for (auto &dest : T->Nodes) {
            if (orig == dest) {
                continue;
            }

            std::shared_ptr<Call> DummyCall(new Call(orig, dest, 0));
            OrigDestPair DummyOrigDest(orig->ID, dest->ID);

            Routes.emplace(DummyOrigDest, DijkstraRoutingAlgorithm::route(DummyCall));
        }
    }
}
