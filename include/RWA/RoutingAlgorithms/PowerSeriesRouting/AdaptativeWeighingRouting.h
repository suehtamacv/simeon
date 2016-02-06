#ifndef ADAPTATIVEWEIGHINGROUTING_H
#define ADAPTATIVEWEIGHINGROUTING_H

#include "PowerSeriesRouting.h"

class AdaptativeWeighingRouting : public PowerSeriesRouting
{
public:
    AdaptativeWeighingRouting(std::shared_ptr<Topology> T);
    AdaptativeWeighingRouting(std::shared_ptr<Topology> T,
                              std::vector<std::shared_ptr<PSR::Cost>> Costs);
    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);
};

#endif // ADAPTATIVEWEIGHINGROUTING_H
