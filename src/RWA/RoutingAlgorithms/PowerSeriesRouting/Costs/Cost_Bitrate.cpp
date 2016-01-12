#include <RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Bitrate.h>
#include <algorithm>
#include "Calls.h"

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

        for (int n = NMin; n <= NMax; n++)
            {
            cache.at(bitrate)(expo++) = pow(bitrate.get_Bitrate() / maxBitrate, n);
            }
        }
}
