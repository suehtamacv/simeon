#ifndef CORIGDESTINDEX_H
#define CORIGDESTINDEX_H

#include <map>
#include "Cost.h"

namespace RMSA
{
namespace ROUT
{
namespace PSR
{

/**
 * @brief The cOrigDestIndex class has, as cost, the index of this origin destination
 * pair. The pairs are put in a crescent list [0-1 0-2 ... 1-0 1-2 ... N-(N-1) ],
 * with N * (N-1) elements. Each origin destination pair will have, as cost, its
 * index on the list normalized by N * (N-1).
 */
class cOrigDestIndex : public Cost
{
public:
    /**
     * @brief cOrigDestIndex is the standard constructor for the cOrigDestIndex cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cOrigDestIndex(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link>, std::shared_ptr<Call>);
    double getUnitCost(std::weak_ptr<Link>, std::shared_ptr<Call>);

private:
    void createCache();
    std::map<std::pair<int, int>, arma::rowvec> cache;
    std::map<std::pair<int, int>, double> unitCache;
};
}
}
}

#endif // CORIGDESTINDEX_H
