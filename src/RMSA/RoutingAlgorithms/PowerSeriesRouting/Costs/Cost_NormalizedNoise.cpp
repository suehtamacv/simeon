#include <RMSA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_NormalizedNoise.h>
#include <Calls/Call.h>
#include <Structure.h>
#include <map>

using namespace RMSA::ROUT;

PSR::cNormNoise::cNormNoise(int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::normnoise)
{
    createCache();
}

arma::rowvec PSR::cNormNoise::getCost(
    std::weak_ptr<Link> link, std::shared_ptr<Call>)
{
    return cache.at(link.lock());
}

void PSR::cNormNoise::createCache()
{
    double maxNoise = -1;
    for (auto link : T->Links)
        {
        Signal S;
        S = link.second->Origin.lock()->add(S);
        S = link.second->bypass(S);
        S = link.second->Destination.lock()->drop(S);
        double NoisePower = S.get_NoisePower().in_Watts();

        if (maxNoise < NoisePower)
            {
            maxNoise = NoisePower;
            }
        }

    for (auto link : T->Links)
        {
        Signal S;
        S = link.second->Origin.lock()->add(S);
        S = link.second->bypass(S);
        S = link.second->Destination.lock()->drop(S);
        double NoisePower = S.get_NoisePower().in_Watts();

        cache.emplace(link.second, arma::ones<arma::rowvec>(NMax - NMin + 1));
        int expo = 0;

        for (int n = NMin; n <= NMax; n++)
            {
            cache.at(link.second)(expo++) = pow(NoisePower / maxNoise, n);
            }
        }
}
