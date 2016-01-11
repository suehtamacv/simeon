#include <RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_Noise.h>
#include <Structure.h>
#include <Calls/Call.h>

PSR::cNoise::cNoise(
    int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::noise) {
    createCache();
}

arma::rowvec PSR::cNoise::getCost(std::weak_ptr<Link> link,
                                  std::shared_ptr<Call> C) {
    return cache.at(CallProperties{link, C->Bitrate, C->Scheme});
}

void PSR::cNoise::createCache() {
    for (auto link : T->Links) {
        Signal S;
        S = link.second->Origin.lock()->add(S);
        S = link.second->bypass(S);
        S = link.second->Destination.lock()->drop(S);
        double NoisePower = S.get_NoisePower().in_Watts();

        for (auto &bitrate : TransmissionBitrate::DefaultBitrates) {
            for (auto &scheme : ModulationScheme::DefaultSchemes) {
                CallProperties Prop{link.second, bitrate, scheme};
                double ThresholdNoise = (Signal::InputPower * -scheme.get_ThresholdOSNR(bitrate))
                                        .in_Watts();

                cache.emplace(Prop, arma::ones<arma::rowvec>(NMax - NMin + 1));
                int expo = 0;

                for (int n = NMin; n <= NMax; n++) {
                    cache.at(Prop)(expo++) = pow(NoisePower / ThresholdNoise, n);
                }
            }
        }
    }
}
