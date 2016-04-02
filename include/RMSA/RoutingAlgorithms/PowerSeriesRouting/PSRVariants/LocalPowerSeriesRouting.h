#ifndef LOCALPOWERSERIESROUTING_H
#define LOCALPOWERSERIESROUTING_H

#include "../PowerSeriesRouting.h"
#include <vector>
#include <map>

class LocalPowerSeriesRouting : public PowerSeriesRouting
{
public:
    LocalPowerSeriesRouting(std::shared_ptr<Topology> T);
    LocalPowerSeriesRouting(std::shared_ptr<Topology> T,
                            std::vector<std::shared_ptr<PSR::Cost>> Costs);
    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

private:
    void calculateCoefficients(std::pair<int, int>);
    std::map<std::pair<int, int>, arma::mat> coef_matrices;
    std::vector<std::pair<int, int>> origDestPairs;
};

#endif // LOCALPOWERSERIESROUTING_H
