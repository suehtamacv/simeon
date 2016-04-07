#include <RMSA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_NormalizedContiguity.h>
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

void PSR::cNormContiguity::createCache()
{
    for (int contig = 0; contig <= Link::NumSlots; contig++)
        {
        int expo = 0;

        for (int n = NMin; n <= NMax; n++)
            {
            cache(contig, expo++) = pow(contig / (1.0 * Link::NumSlots), n);
            }
        }
}
