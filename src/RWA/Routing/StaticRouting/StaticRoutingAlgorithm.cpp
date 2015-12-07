#include <RWA/Routing/StaticRouting/StaticRoutingAlgorithm.h>

StaticRoutingAlgorithm::StaticRoutingAlgorithm(std::shared_ptr<Topology> T) :
    DijkstraRoutingAlgorithm(T) {
}

std::vector<std::weak_ptr<Link>> StaticRoutingAlgorithm::route(Call C) {
    if (Routes.empty()) {
        precalculate_Routes();
    }

    OrigDestPair OrigDest(C.Origin.lock()->ID, C.Destination.lock()->ID);
    return Routes[OrigDest];
}

void StaticRoutingAlgorithm::precalculate_Routes() {
    for (auto orig : T->Nodes) {
        for (auto dest : T->Nodes) {
            if (orig == dest) {
                continue;
            }

            Call DummyCall(0, 1, orig, dest, 0);
            OrigDestPair DummyOrigDest(orig->ID, dest->ID);

            Routes.emplace(DummyOrigDest, DijkstraRoutingAlgorithm::route(DummyCall));
        }
    }
}
