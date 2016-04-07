#ifndef CSLOTS_H
#define CSLOTS_H

#include "Cost.h"
#include <map>

namespace ROUT
{
namespace PSR
{

/**
 * @brief The cSlots class has, as cost, the quantity of slots required by this
 * connection, normalized by the highest possible amount of slots required by
 * any connection.
 */
class cSlots : public Cost
{
public:
    /**
     * @brief cSlots is the standard constructor for the cSlots cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cSlots(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link>, std::shared_ptr<Call>);

private:
    void createCache();
    std::map<unsigned int, arma::rowvec> cache;
};

}
}

#endif // CSLOTS_H
