#include "include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_HopDistance.h"
#include <set>
#include <Calls/Call.h>
#include <GeneralClasses/TransmissionBitrate.h>
#include <RWA/RoutingAlgorithms/StaticRouting/MinimumHops.h>
#include <Structure/Link.h>
#include <Structure/Topology.h>

PSR::cHopDistance::cHopDistance(int NMin, int NMax, std::shared_ptr<Topology> T)
    : Cost(NMin, NMax, T, Cost::hopdistance)
{
    createCache();
}

arma::rowvec PSR::cHopDistance::getCost(std::weak_ptr<Link>,
                                        std::shared_ptr<Call> C)
{
    return cache.at(std::make_pair(C->Origin.lock()->ID,
                                   C->Destination.lock()->ID));
}

PSR::cHopDistance::Comparator::Comparator
(int OrigID, int DestID, double RouteLength, unsigned int NumHops) :
    OrigID(OrigID), DestID(DestID), RouteLength(RouteLength), NumHops(NumHops)
{ }

bool PSR::cHopDistance::Comparator::operator <(const Comparator &other) const
{
    if (NumHops < other.NumHops)
        {
        return true;
        }
    else if (NumHops == other.NumHops)
        {
        if (RouteLength < other.RouteLength)
            {
            return true;
            }
        else if (RouteLength == other.RouteLength)
            {
            if (OrigID < other.OrigID)
                {
                return true;
                }
            else if (OrigID == other.OrigID && DestID < other.DestID)
                {
                return true;
                }
            }
        }
    return false;
}


void PSR::cHopDistance::createCache()
{
    std::set<Comparator> MinimalDistance;
    auto MH = std::make_shared<MinimumHops>(T);

    for (auto &orig : T->Nodes)
        {
        for (auto &dest : T->Nodes)
            {
            if (orig == dest)
                {
                continue;
                }

            auto DummyCall = std::make_shared<Call>
                             (orig, dest, TransmissionBitrate::DefaultBitrates.front());
            auto Links = MH->route(DummyCall);
            double RouteLength = 0;

            for (auto &link : Links)
                {
                RouteLength += link.lock()->Length;
                }

            MinimalDistance.emplace(
                Comparator(orig->ID, dest->ID, RouteLength, Links.size()));
            }
        }

    int Index = 1;
    for (auto &comp : MinimalDistance)
        {
        auto OrigDestPair = std::make_pair(comp.OrigID, comp.DestID);
        cache.emplace(OrigDestPair, arma::ones<arma::rowvec>(NMax - NMin + 1));
        int expo = 0;

        for (int n = NMin; n <= NMax; n++)
            {
            cache.at(OrigDestPair)(expo++) = pow((1.0 * Index) / MinimalDistance.size(), n);
            }
        Index++;
        }
}
