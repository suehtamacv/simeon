#include <RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/AdaptativeWeighingRouting.h>
#include <RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost.h>

AdaptativeWeighingRouting::AdaptativeWeighingRouting(
    std::shared_ptr<Topology> T) : PowerSeriesRouting(T, RoutingAlgorithm::AWR)
{
}

AdaptativeWeighingRouting::AdaptativeWeighingRouting(std::shared_ptr<Topology>
        T, std::vector<std::shared_ptr<PSR::Cost>> Costs) :
    PowerSeriesRouting(T, Costs, RoutingAlgorithm::AWR)
{
}

double AdaptativeWeighingRouting::get_Cost(
    std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
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
