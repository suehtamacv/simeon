#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost_Availability.h>
#include <Structure/Link.h>
#include <Calls/Call.h>
#include <cmath>

using namespace RMSA::ROUT;

PSR::cAvailability::cAvailability(int NMin, int NMax,
                                  std::shared_ptr<Topology> T)
    : Cost(NMin, NMax, T, Cost::availability)
{
    cache = arma::ones<arma::mat>(Link::NumSlots + 1, NMax - NMin + 1);
    createCache();
}

arma::rowvec PSR::cAvailability::getCost(std::weak_ptr<Link> link,
        std::shared_ptr<Call>)
{
    return cache.row(link.lock()->get_Availability());
}

double PSR::cAvailability::getUnitCost(std::weak_ptr<Link> link, std::shared_ptr<Call>)
{
    return unitCache[link.lock()->get_Availability()];
}

void PSR::cAvailability::createCache()
{
    for (int avail = 0; avail <= Link::NumSlots; avail++)
        {
        int expo = 0;
        double unitCost = avail / (double) Link::NumSlots;

        unitCache[avail] = unitCost;
        for (int n = NMin; n <= NMax; n++)
            {
            cache(avail, expo++) = pow(unitCost, n);
            }
        }
}
