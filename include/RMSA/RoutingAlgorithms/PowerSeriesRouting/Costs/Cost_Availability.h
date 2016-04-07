#ifndef COST_AVAILABILITY
#define COST_AVAILABILITY

#include "Cost.h"

namespace RMSA {
namespace ROUT
{
namespace PSR
{

/**
* @brief The cAvailability class has, as cost, the number of free slots on
* each link, normalized by the number of slots on each link.
*/
class cAvailability : public Cost
{
public:
    /**
     * @brief cAvailability is the standard constructor for the cAvailability cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cAvailability(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);

private:
    void createCache();
    arma::mat cache;
};

}
}
}

#endif // COST_AVAILABILITY

