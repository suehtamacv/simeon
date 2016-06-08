#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost_OrigDestIndex.h>
#include <Structure/Node.h>
#include <Structure/Topology.h>
#include <Calls/Call.h>
#include <set>

using namespace RMSA::ROUT;

PSR::cOrigDestIndex::cOrigDestIndex
(int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, origdestindex)
{
    createCache();
}

arma::rowvec PSR::cOrigDestIndex::getCost
(std::weak_ptr<Link>, std::shared_ptr<Call> C)
{
    return cache.at({C->Origin.lock()->ID, C->Destination.lock()->ID});
}

void PSR::cOrigDestIndex::createCache()
{
    int Index = 1;
    int numPairs = T->Nodes.size() * (T->Nodes.size() - 1);

    for (auto &orig : T->Nodes)
        {
        for (auto &dest : T->Nodes)
            {
            if (orig == dest)
                {
                continue;
                }

            auto OrigDestPair = std::make_pair(orig->ID, dest->ID);
            cache.emplace(OrigDestPair, arma::ones<arma::rowvec>(NMax - NMin + 1));
            int expo = 0;

            for (int n = NMin; n <= NMax; n++)
                {
                cache.at(OrigDestPair)(expo++) = pow((1.0 * Index) / numPairs, n);
                }
            Index++;
            }
        }
}
