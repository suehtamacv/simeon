#ifndef MATRICIALPOWERSERIESROUTING_H
#define MATRICIALPOWERSERIESROUTING_H

#include "../PowerSeriesRouting.h"

namespace RMSA
{
namespace ROUT
{
namespace PSR
{
/**
 * @brief The MatricialPowerSeriesRouting class is the standard Power Series Routing
 * algorithm. Its cost is a truncated power series of carefully chosen costs.
 */
class MatricialPowerSeriesRouting : public PowerSeriesRouting
{
public:
    MatricialPowerSeriesRouting(std::shared_ptr<Topology> T);
    MatricialPowerSeriesRouting(std::shared_ptr<Topology> T,
                                std::vector<std::shared_ptr<PSR::Cost>> Costs);
    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

    std::map<std::vector<double>, double> cache;
};
}
}
}

#endif // MATRICIALPOWERSERIESROUTING_H
