#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost_NormalizedContiguity.h>
#include <Structure/Link.h>

using namespace RMSA::ROUT;

PSR::cNormContiguity::cNormContiguity(
    int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::normcontiguity)
{
    cache = arma::ones<arma::mat>(Link::NumSlots + 1, NMax - NMin + 1);
    createCache();
}

arma::rowvec PSR::cNormContiguity::getCost(std::weak_ptr<Link> link,
        std::shared_ptr<Call> C)
{
    return cache.row(link.lock()->get_Contiguity(C));
}

double PSR::cNormContiguity::getUnitCost(std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
    return unitCache[link.lock()->get_Contiguity(C)];
}

void PSR::cNormContiguity::createCache()
{
    for (int contig = 0; contig <= Link::NumSlots; contig++)
        {
        int expo = 0;
        double unitCost = contig / (1.0 * Link::NumSlots);

        unitCache[contig] = unitCost;
        for (int n = NMin; n <= NMax; n++)
            {
            cache(contig, expo++) = pow(unitCost, n);
            }
        }
}
