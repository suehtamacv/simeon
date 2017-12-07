#ifndef COST_NORMALIZEDCONTIGUITY_H
#define COST_NORMALIZEDCONTIGUITY_H

#include "Cost.h"
#include "GeneralClasses/TransmissionBitrate.h"
#include "GeneralClasses/ModulationScheme.h"
#include <map>

namespace RMSA
{
namespace ROUT
{
namespace PSR
{

/**
* @brief The cNormContiguity class has, as cost, the contiguity
* measure of the link. It only works on transparent networks. If sr is the
* number of possible allocations of the call C in the Link link, then this
* cost is sr / SR.
*/
class cNormContiguity : public Cost
{
public:
    /**
     * @brief cNormContiguity is the standard constructor for the cNormContiguity cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cNormContiguity(int NMin, int NMax, std::shared_ptr<Topology> T);
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

#endif // COST_NORMALIZEDCONTIGUITY_H

