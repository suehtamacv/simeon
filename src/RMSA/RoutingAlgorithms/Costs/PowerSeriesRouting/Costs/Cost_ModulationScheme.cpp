#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost_ModulationScheme.h>
#include <Calls/Call.h>

using namespace RMSA::ROUT;

PSR::cModulationScheme::cModulationScheme(
    int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::scheme)
{
    createCache();
}

arma::rowvec PSR::cModulationScheme::getCost(std::weak_ptr<Link>,
        std::shared_ptr<Call> C)
{
    return cache[C->Scheme];
}

double PSR::cModulationScheme::getUnitCost(std::weak_ptr<Link>, std::shared_ptr<Call> C)
{
    return unitCache[C->Scheme];
}

void PSR::cModulationScheme::createCache()
{
    double maxScheme = -1;

    for (auto &scheme : ModulationScheme::DefaultSchemes)
        {
        if (maxScheme < scheme.get_M())
            {
            maxScheme = scheme.get_M();
            }
        }

    for (auto &scheme : ModulationScheme::DefaultSchemes)
        {
        cache.emplace(scheme, arma::rowvec(NMax - NMin + 1));

        int expo = 0;
        double unitCost = scheme.get_M() / maxScheme;

        unitCache[scheme] = unitCost;
        for (int n = NMin; n <= NMax; n++)
            {
            cache.at(scheme)(expo++) = pow(unitCost, n);
            }
        }
}

