#ifndef TENSORIALPOWERSERIESROUTING_H
#define TENSORIALPOWERSERIESROUTING_H

#include "../PowerSeriesRouting.h"

namespace ROUT
{
namespace PSR
{
/**
 * @brief The TensorialPowerSeriesRouting class is a type of Power Series Routing
 * algorithm. Differently from MatricialPowerSeriesRouting, this PSR uses the
 * Krönecker product to produce, from a reduced set of coefficients, the large set
 * required to calculate the power series.
 */
class TensorialPowerSeriesRouting : public PowerSeriesRouting
{
public:
    TensorialPowerSeriesRouting(std::shared_ptr<Topology> T);
    TensorialPowerSeriesRouting(std::shared_ptr<Topology> T,
                                std::vector<std::shared_ptr<PSR::Cost>> Costs);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

private:
    arma::mat coefs_matrix;
    void calculate_CoefsMatrix();
};
}
}

#endif // TENSORIALPOWERSERIESROUTING_H
