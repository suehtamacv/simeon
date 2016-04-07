#include <RMSA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Occupability.h>
#include <Structure/Link.h>
#include <Calls/Call.h>
#include <cmath>

using namespace RMSA::ROUT;

PSR::cOccupability::cOccupability(int NMin, int NMax,
                                  std::shared_ptr<Topology> T)
    : Cost(NMin, NMax, T, Cost::occupability)
{
    cache = arma::ones<arma::mat>(Link::NumSlots + 1, NMax - NMin + 1);
    createCache();
}

arma::rowvec PSR::cOccupability::getCost(std::weak_ptr<Link> link,
        std::shared_ptr<Call>)
{
    return cache.row(link.lock()->get_Occupability());
}

void PSR::cOccupability::createCache()
{
    for (int occup = 0; occup <= Link::NumSlots; occup++)
        {
        int expo = 0;

        for (int n = NMin; n <= NMax; n++)
            {
            cache(occup, expo++) = pow(occup / (double) Link::NumSlots, n);
            }
        }
}

