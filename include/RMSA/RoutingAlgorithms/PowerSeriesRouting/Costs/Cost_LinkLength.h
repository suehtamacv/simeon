#ifndef CLINKLENGTH_H
#define CLINKLENGTH_H

#include "Cost.h"
#include <map>

namespace RMSA
{
namespace ROUT
{
namespace PSR
{

/**
 * @brief The cLinkLength class has, as cost, how big this link is compared to the
 * other links in the topology. The links are put in crescent order, from 0 to N,
 * and then the i-th link on the list will have i/N as cost.
 */
class cLinkLength : public Cost
{
public:
    /**
     * @brief cLinkLength is the standard constructor for the cLinkLength cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cLinkLength(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);

private:
    void createCache();
    std::map<std::shared_ptr<Link>, arma::rowvec> cache;

    struct Comparator
    {
        std::weak_ptr<Link> link;
        bool operator <(const Comparator &) const;
    };
};

}
}
}

#endif // CLINKLENGTH_H
