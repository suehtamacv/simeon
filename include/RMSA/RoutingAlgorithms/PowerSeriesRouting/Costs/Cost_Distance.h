#ifndef COST_DISTANCE
#define COST_DISTANCE

#include "Cost.h"
#include <map>

namespace ROUT
{
namespace PSR
{
/**
* @brief The cDistance class has, as cost, the length of the link, normalized
* by the length of the longest link of the topology.
*/
class cDistance : public Cost
{
public:
    cDistance(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);

private:
    void createCache();
    std::map<std::shared_ptr<Link>, arma::rowvec> cache;
};

}
}

#endif // COST_DISTANCE
