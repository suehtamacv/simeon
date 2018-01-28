#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/PSRVariants/MatricialPowerSeriesRouting.h>
#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost.h>
#include <Structure/Link.h>

using namespace RMSA::ROUT::PSR;

MatricialPowerSeriesRouting::MatricialPowerSeriesRouting
(std::shared_ptr<Topology> T) : PowerSeriesRouting(T, RoutingCost::matPSR)
{
    Variant = Variant_MatricialPSR;
}

MatricialPowerSeriesRouting::MatricialPowerSeriesRouting
(std::shared_ptr<Topology> T, std::vector<std::shared_ptr<PSR::Cost>> Costs) :
    PowerSeriesRouting(T, Costs, RoutingCost::matPSR)
{
    Variant = Variant_MatricialPSR;
}

double MatricialPowerSeriesRouting::get_Cost
(std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
    if (!link.lock()->is_LinkActive())
        {
        return std::numeric_limits<double>::max();
        }

    std::vector<double> costs;
    for (auto &cost : Costs)
        {
        costs.push_back(cost->getUnitCost(link, C));
        }

    if (cache.count(costs))
        {
        return cache[costs];
        }
    else
        {
        arma::mat cost_matrix = arma::ones(1);

        for (auto &cost : Costs)
            {
            cost_matrix = arma::kron(cost_matrix, cost->getCost(link, C));
            }

        if (!firstTimeRun)
            {
            coefficients.copy_size(cost_matrix);
            firstTimeRun = true;
            }

        double totalCost = arma::accu(coefficients % cost_matrix);
        cache[costs] = totalCost;

        return totalCost;
        }
}
