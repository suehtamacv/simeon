#include <RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_NormalizedNoise.h>
#include <Calls/Call.h>
#include <Structure.h>
#include <map>

PSR::cNormNoise::cNormNoise(int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::normnoise)
{
    createCache();
}

arma::rowvec PSR::cNormNoise::getCost(
    std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
    return cache.at(CallProperties{link, C->Bitrate, C->Scheme});
}

void PSR::cNormNoise::createCache()
{
    double maxNoiseToThresh = -1;
    for (auto link : T->Links)
        {
        Signal S;
        S = link.second->Origin.lock()->add(S);
        S = link.second->bypass(S);
        S = link.second->Destination.lock()->drop(S);
        double NoisePower = S.get_NoisePower().in_Watts();

        for (auto &bitrate : TransmissionBitrate::DefaultBitrates)
            {
            for (auto &scheme : ModulationScheme::DefaultSchemes)
                {
                double ThresholdNoise =
                    (Signal::InputPower * -scheme.get_ThresholdOSNR(bitrate))
                    .in_Watts();
                if (maxNoiseToThresh < NoisePower / ThresholdNoise)
                    {
                    maxNoiseToThresh = NoisePower / ThresholdNoise;
                    }
                }
            }
        }

    for (auto link : T->Links)
        {
        Signal S;
        S = link.second->Origin.lock()->add(S);
        S = link.second->bypass(S);
        S = link.second->Destination.lock()->drop(S);
        double NoisePower = S.get_NoisePower().in_Watts();

        for (auto &bitrate : TransmissionBitrate::DefaultBitrates)
            {
            for (auto &scheme : ModulationScheme::DefaultSchemes)
                {
                CallProperties Prop{link.second, bitrate, scheme};
                double ThresholdNoise =
                    (Signal::InputPower * -scheme.get_ThresholdOSNR(bitrate))
                    .in_Watts();

                cache.emplace(Prop, arma::ones<arma::rowvec>(NMax - NMin + 1));
                int expo = 0;

                for (int n = NMin; n <= NMax; n++)
                    {
                    cache.at(Prop)(expo++) =
                        pow(NoisePower / (ThresholdNoise * maxNoiseToThresh), n);
                    }
                }
            }
        }
}
