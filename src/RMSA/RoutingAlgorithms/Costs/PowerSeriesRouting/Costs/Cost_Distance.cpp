#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost_Distance.h>
#include <Structure/Link.h>
#include <Structure/Topology.h>
#include <Calls/Call.h>
#include <cmath>

using namespace RMSA::ROUT;

PSR::cDistance::cDistance(int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::distance)
{
    createCache();
}

arma::rowvec PSR::cDistance::getCost(std::weak_ptr<Link> link,
                                     std::shared_ptr<Call>)
{
    return cache.at(link.lock());
}

void PSR::cDistance::createCache()
{
    for (auto link : T->Links)
        {
        cache.emplace(link.second, arma::ones<arma::rowvec>(NMax - NMin + 1));
        int expo = 0;

        for (int n = NMin; n <= NMax; n++)
            {
            cache.at(link.second)(expo++) = pow(link.second->Length /
                                                T->get_LengthLongestLink(), n);
            }
        }
}
