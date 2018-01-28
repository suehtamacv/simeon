#ifndef COST_OCCUPABILITY_H
#define COST_OCCUPABILITY_H

#include "Cost.h"

namespace RMSA
{
namespace ROUT
{
namespace PSR
{
/**
* @brief The cOccupability class has, as cost, the number of occupied slots
* on each link, normalized by the number of slots on each link.
*/
class cOccupability : public Cost
{
public:
    /**
     * @brief cOccupability is the standard constructor for the cOccupability cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cOccupability(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);
    double getUnitCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);

private:
    void createCache();
    arma::mat cache;
    std::map<unsigned int, double> unitCache;
};

}
}
}

#endif // COST_OCCUPABILITY_H

