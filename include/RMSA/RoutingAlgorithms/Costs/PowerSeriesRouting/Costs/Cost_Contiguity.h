#ifndef COST_CONTIGUITY_H
#define COST_CONTIGUITY_H

#include "Cost.h"

namespace RMSA
{
namespace ROUT
{
namespace PSR
{

/**
* @brief The cContiguity class has, as cost, the contiguity measure of the
* link. It only works on transparent networks. If sr is the number of
* possible allocations of the call C in the Link link, then this cost is
* 1.0 / (sr + 1).
*/
class cContiguity : public Cost
{
public:
    /**
     * @brief cContiguity is the standard constructor for the cContiguity cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cContiguity(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);
    double getUnitCost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

private:
    void createCache();
    arma::mat cache;
    std::map<unsigned int, double> unitCache;
};

}
}
}

#endif // COST_CONTIGUITY_H
