#include <RMSA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/LocalPowerSeriesRouting.h>
#include <RMSA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost.h>
#include <Calls/Call.h>
#include <Structure/Node.h>
#include <Structure/Topology.h>
#include <algorithm>

using namespace ROUT;

LocalPowerSeriesRouting::LocalPowerSeriesRouting(std::shared_ptr<Topology> T)
    : PowerSeriesRouting(T, localPSR)
{
    for (unsigned orig = 1; orig <= T->Nodes.size(); ++orig)
        {
        for (unsigned dest = 1; dest <= T->Nodes.size(); ++dest)
            {
            if (orig == dest)
                {
                continue;
                }
            origDestPairs.push_back(std::make_pair(orig, dest));
            }
        }
    std::sort(origDestPairs.begin(), origDestPairs.end());

    Variant = Variant_LocalPSR;
}

LocalPowerSeriesRouting::LocalPowerSeriesRouting
(std::shared_ptr<Topology> T, std::vector<std::shared_ptr<PSR::Cost>> Costs)
    : PowerSeriesRouting(T, Costs, localPSR)
{
    for (unsigned orig = 1; orig <= T->Nodes.size(); ++orig)
        {
        for (unsigned dest = 1; dest <= T->Nodes.size(); ++dest)
            {
            if (orig == dest)
                {
                continue;
                }
            origDestPairs.push_back(std::make_pair(orig, dest));
            }
        }
    std::sort(origDestPairs.begin(), origDestPairs.end());

    Variant = Variant_LocalPSR;
}

double LocalPowerSeriesRouting::get_Cost
(std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
    arma::mat cost_matrix = arma::ones(1);
    auto origDestPair = std::make_pair(C->Origin.lock()->ID,
                                       C->Destination.lock()->ID);

    for (auto &cost : Costs)
        {
        cost_matrix = arma::kron(cost_matrix, cost->getCost(link, C));
        }

    if (!coef_matrices.count(origDestPair))
        {
        calculateCoefficients(origDestPair);
        coef_matrices.at(origDestPair).copy_size(cost_matrix);
        }

    return arma::accu(coef_matrices.at(origDestPair) % cost_matrix);
}

void LocalPowerSeriesRouting::calculateCoefficients
(std::pair<int, int> origDestPair)
{
    if (coef_matrices.count(origDestPair))
        {
        return;
        }

    int pos = std::distance(origDestPairs.begin(),
                            std::find(origDestPairs.begin(), origDestPairs.end(), origDestPair));
    coef_matrices.emplace(origDestPair,
                          coefficients.cols(pos, pos + std::pow(NMax - NMin + 1, Costs.size()) - 1));
}
