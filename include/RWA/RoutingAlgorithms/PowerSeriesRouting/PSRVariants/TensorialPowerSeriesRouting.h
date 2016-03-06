#ifndef TENSORIALPOWERSERIESROUTING_H
#define TENSORIALPOWERSERIESROUTING_H

#include "../PowerSeriesRouting.h"

class TensorialPowerSeriesRouting : public PowerSeriesRouting
{
public:
    TensorialPowerSeriesRouting(std::shared_ptr<Topology> T);
    TensorialPowerSeriesRouting(std::shared_ptr<Topology> T,
                                std::vector<std::shared_ptr<PSR::Cost>> Costs);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

private:
    arma::mat coefs_matrix;
};

#endif // TENSORIALPOWERSERIESROUTING_H
