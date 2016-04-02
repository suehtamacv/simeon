#include "include/RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost_LinkLength.h"
#include <set>
#include <Structure/Link.h>
#include <Structure/Node.h>
#include <Structure/Topology.h>

PSR::cLinkLength::cLinkLength(int NMin, int NMax, std::shared_ptr<Topology> T) :
    Cost(NMin, NMax, T, Cost::linklength)
{
    createCache();
}

arma::rowvec PSR::cLinkLength::getCost
(std::weak_ptr<Link> link, std::shared_ptr<Call>)
{
    return cache.at(link.lock());
}

bool PSR::cLinkLength::Comparator::operator <(const Comparator &other) const
{
    auto locklink = link.lock();
    auto otherlocklink = other.link.lock();

    if (locklink->Length < otherlocklink->Length)
        {
        return true;
        }
    else if (locklink->Length == otherlocklink->Length)
        {
        if (locklink->Origin.lock()->ID < otherlocklink->Origin.lock()->ID)
            {
            return true;
            }
        else if ((locklink->Origin.lock()->ID == otherlocklink->Origin.lock()->ID) &&
                 (locklink->Destination.lock()->ID < otherlocklink->Destination.lock()->ID))
            {
            return true;
            }
        }

    return false;
}

void PSR::cLinkLength::createCache()
{
    std::set<Comparator> LinkComparator;
    for (auto &link : T->Links)
        {
        LinkComparator.emplace(Comparator{link.second});
        }

    int Index = 1;
    for (auto &linkcomp : LinkComparator)
        {
        cache.emplace(linkcomp.link.lock(), arma::ones<arma::rowvec>(NMax - NMin + 1));
        int expo = 0;

        for (int n = NMin; n <= NMax; n++)
            {
            cache.at(linkcomp.link.lock())(expo++) =
                pow((1.0 * Index) / LinkComparator.size(), n);
            }
        Index++;
        }
}
