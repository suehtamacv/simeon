#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost_Bitrate.h>
#include <algorithm>
#include "Calls.h"

using namespace RMSA::ROUT;

PSR::cBitrate::cBitrate(int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::bitrate)
{
    createCache();
}

arma::rowvec PSR::cBitrate::getCost(std::weak_ptr<Link>,
                                    std::shared_ptr<Call> C)
{
    return cache[C->Bitrate];
}

double PSR::cBitrate::getUnitCost(std::weak_ptr<Link>, std::shared_ptr<Call> C)
{
    return unitCache[C->Bitrate];
}

void PSR::cBitrate::createCache()
{
    double maxBitrate = -1;

    for (auto &bitrate : TransmissionBitrate::DefaultBitrates)
        {
        if (maxBitrate < bitrate.get_Bitrate())
            {
            maxBitrate = bitrate.get_Bitrate();
            }
        }

    for (auto &bitrate : TransmissionBitrate::DefaultBitrates)
        {
        cache.emplace(bitrate, arma::rowvec(NMax - NMin + 1));

        int expo = 0;
        double unitCost = bitrate.get_Bitrate() / maxBitrate;

        unitCache[bitrate] = unitCost;
        for (int n = NMin; n <= NMax; n++)
            {
            cache.at(bitrate)(expo++) = pow(unitCost, n);
            }
        }
}
