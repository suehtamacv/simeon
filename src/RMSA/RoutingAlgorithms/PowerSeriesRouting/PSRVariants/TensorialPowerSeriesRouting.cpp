#include <RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/TensorialPowerSeriesRouting.h>
#include <RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost.h>

TensorialPowerSeriesRouting::TensorialPowerSeriesRouting
(std::shared_ptr<Topology> T) : PowerSeriesRouting(T, RoutingAlgorithm::tenPSR)
{
    Variant = Variant_TensorialPSR;
}

TensorialPowerSeriesRouting::TensorialPowerSeriesRouting
(std::shared_ptr<Topology> T, std::vector<std::shared_ptr<PSR::Cost>> Costs) :
    PowerSeriesRouting(T, Costs, RoutingAlgorithm::tenPSR)
{
    Variant = Variant_TensorialPSR;
}

double TensorialPowerSeriesRouting::get_Cost
(std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
    arma::mat cost_matrix = arma::ones(1);

    for (auto &cost : Costs)
        {
        cost_matrix = arma::kron(cost_matrix, cost->getCost(link, C));
        }

    if (!firstTimeRun)
        {
        calculate_CoefsMatrix();
        coefs_matrix.copy_size(cost_matrix);
        firstTimeRun = true;
        }

    return arma::accu(coefs_matrix % cost_matrix);
}

void TensorialPowerSeriesRouting::calculate_CoefsMatrix()
{
    coefs_matrix = arma::ones(1);
    for (unsigned cost = 0; cost < Costs.size(); ++cost)
        {
        auto costCoefs = coefficients.cols(cost * get_N(), (cost + 1) * get_N() - 1);
        coefs_matrix = arma::kron(coefs_matrix, costCoefs);
        }
}
