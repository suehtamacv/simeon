#ifndef LOCALPOWERSERIESROUTING_H
#define LOCALPOWERSERIESROUTING_H

#include "../PowerSeriesRouting.h"

class LocalPowerSeriesRouting : public PowerSeriesRouting
{
public:
    LocalPowerSeriesRouting(std::shared_ptr<Topology> T);
    LocalPowerSeriesRouting(std::shared_ptr<Topology> T,
                              std::vector<std::shared_ptr<PSR::Cost>> Costs);
    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);
};

#endif // LOCALPOWERSERIESROUTING_H
