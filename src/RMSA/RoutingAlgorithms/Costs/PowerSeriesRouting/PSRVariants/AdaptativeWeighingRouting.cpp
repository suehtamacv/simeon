#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/PSRVariants/AdaptativeWeighingRouting.h>
#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost.h>
#include <Structure/Link.h>

using namespace RMSA::ROUT::PSR;

AdaptativeWeighingRouting::AdaptativeWeighingRouting
(std::shared_ptr<Topology> T) : PowerSeriesRouting(T, RoutingCost::AWR)
{
    Variant = Variant_AWR;
}

AdaptativeWeighingRouting::AdaptativeWeighingRouting(std::shared_ptr<Topology>
        T, std::vector<std::shared_ptr<PSR::Cost>> Costs) :
    PowerSeriesRouting(T, Costs, RoutingCost::AWR)
{
    Variant = Variant_AWR;
}

double AdaptativeWeighingRouting::get_Cost(
    std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
    if (!link.lock()->is_LinkActive())
        {
        return std::numeric_limits<double>::max();
        }

    double Cost = 0;

    //Spherical coordinates for a n-sphere that represents the possible values that the AWR can take.
    double Sines = 1;

    for (unsigned n = 0; n < Costs.size(); ++n)
        {
        Cost += Costs[n]->getCost(1, link, C) * std::cos(coefficients.at(n)) * Sines;
        Sines *= std::sin(coefficients.at(n));
        }

    return Cost;
}
