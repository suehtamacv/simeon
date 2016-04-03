#include <RMSA/RoutingAlgorithms/StaticRouting/FixedRoutingAlgorithm.h>
#include <Calls/Call.h>
#include <Structure/Node.h>
#include <Structure/Topology.h>

using namespace ROUT;

FixedRoutingAlgorithm::FixedRoutingAlgorithm
(std::shared_ptr<Topology> T, RoutingAlgorithms RoutAlg) :
    DijkstraRoutingAlgorithm(T, RoutAlg)
{
}

std::vector<std::weak_ptr<Link>> FixedRoutingAlgorithm::route(
                                  std::shared_ptr<Call> C)
{
    if (Routes.empty())
        {
        precalculate_Routes();
        }

    return Routes[std::make_pair(C->Origin.lock()->ID, C->Destination.lock()->ID)];
}

void FixedRoutingAlgorithm::precalculate_Routes()
{
    for (auto &orig : T->Nodes)
        {
        for (auto &dest : T->Nodes)
            {
            if (orig == dest)
                {
                continue;
                }

            std::shared_ptr<Call> DummyCall(new Call(orig, dest, 0));
            auto DummyOrigDest = std::make_pair(orig->ID, dest->ID);

            Routes.emplace(DummyOrigDest, DijkstraRoutingAlgorithm::route(DummyCall));
            }
        }
}
