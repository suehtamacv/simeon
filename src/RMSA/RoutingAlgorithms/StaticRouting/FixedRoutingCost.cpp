#include <RMSA/RoutingAlgorithms/StaticRouting/FixedRoutingCost.h>
#include <Calls/Call.h>
#include <Structure/Node.h>
#include <Structure/Topology.h>

using namespace RMSA::ROUT;

FixedRoutingCost::FixedRoutingCost
(std::shared_ptr<Topology> T, RoutingCosts RoutCost) :
    RoutingCost(T, RoutCost)
{

}

std::vector<std::vector<std::weak_ptr<Link>>>
FixedRoutingCost::route(std::shared_ptr<Call> C)
{
    if (Routes.empty())
        {
        precalculate_Routes();
        }

    return Routes[std::make_pair(C->Origin.lock()->ID, C->Destination.lock()->ID)];
}

void FixedRoutingCost::precalculate_Routes()
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

            Routes.emplace(DummyOrigDest, RoutingAlgorithm::route(DummyCall));
            }
        }
}
