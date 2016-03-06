#ifndef MATRICIALPOWERSERIESROUTING_H
#define MATRICIALPOWERSERIESROUTING_H

#include "../PowerSeriesRouting.h"

class MatricialPowerSeriesRouting : public PowerSeriesRouting
{
public:
    MatricialPowerSeriesRouting(std::shared_ptr<Topology> T);
    MatricialPowerSeriesRouting(std::shared_ptr<Topology> T,
                                std::vector<std::shared_ptr<PSR::Cost>> Costs);
    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);
};

#endif // MATRICIALPOWERSERIESROUTING_H
