#ifndef ADAPTATIVEWEIGHINGROUTING_H
#define ADAPTATIVEWEIGHINGROUTING_H

#include "../PowerSeriesRouting.h"

namespace ROUT
{
/**
 * @brief The AdaptativeWeighingRouting class represents the Adaptative
 * Weighing Routing algorithm. It is a type of PSR algorithm. Its cost is a power
 * series with only exponent 1.
 */
class AdaptativeWeighingRouting : public PowerSeriesRouting
{
public:
    AdaptativeWeighingRouting(std::shared_ptr<Topology> T);
    AdaptativeWeighingRouting(std::shared_ptr<Topology> T,
                              std::vector<std::shared_ptr<PSR::Cost>> Costs);
    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);
};
}

#endif // ADAPTATIVEWEIGHINGROUTING_H
