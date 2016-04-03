#include <RMSA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Slots.h>
#include "Calls/Call.h"

using namespace ROUT;

PSR::cSlots::cSlots(int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::slots)
{
    createCache();
}

arma::rowvec PSR::cSlots::getCost(std::weak_ptr<Link>, std::shared_ptr<Call> C)
{
    return cache.at(C->Scheme.get_NumSlots(C->Bitrate));
}

void PSR::cSlots::createCache()
{
    unsigned int maxSlots = 1;
    for (auto scheme : ModulationScheme::DefaultSchemes)
        {
        for (auto bitrate : TransmissionBitrate::DefaultBitrates)
            {
            if (maxSlots < scheme.get_NumSlots(bitrate))
                {
                maxSlots = scheme.get_NumSlots(bitrate);
                }
            }
        }

    for (auto scheme : ModulationScheme::DefaultSchemes)
        {
        for (auto bitrate : TransmissionBitrate::DefaultBitrates)
            {
            unsigned int numSlots = scheme.get_NumSlots(bitrate);
            cache.emplace(numSlots, arma::ones<arma::rowvec>(NMax - NMin + 1));
            int expo = 0;

            for (int n = NMin; n <= NMax; n++)
                {
                cache.at(numSlots)(expo++) = pow(numSlots / maxSlots, n);
                }
            }
        }
}
