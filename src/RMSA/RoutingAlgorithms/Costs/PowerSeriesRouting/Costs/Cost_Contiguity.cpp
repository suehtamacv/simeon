#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost_Contiguity.h>
#include <Structure/Link.h>

using namespace RMSA::ROUT;

PSR::cContiguity::cContiguity(int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::contiguity)
{
    cache = arma::ones<arma::mat>(Link::NumSlots + 1, NMax - NMin + 1);
    createCache();
}

arma::rowvec PSR::cContiguity::getCost(std::weak_ptr<Link> link,
                                       std::shared_ptr<Call> C)
{
    return cache.row(link.lock()->get_Contiguity(C));
}

double PSR::cContiguity::getUnitCost(std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
    return unitCache[link.lock()->get_Contiguity(C)];
}

void PSR::cContiguity::createCache()
{
    for (int contig = 0; contig <= Link::NumSlots; contig++)
        {
        int expo = 0;
        double unitCost = 1.0 / (contig + 1);

        unitCache[contig] = unitCost;
        for (int n = NMin; n <= NMax; n++)
            {
            cache(contig, expo++) = pow(unitCost, n);
            }
        }
}
