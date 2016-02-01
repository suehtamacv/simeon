#include "include/RWA/RoutingAlgorithms/PowerSeriesRouting/AdaptativeWeighingRouting.h"

AdaptativeWeighingRouting::AdaptativeWeighingRouting(
    std::shared_ptr<Topology> T) : PowerSeriesRouting(T)
{
    RoutAlgType = AWR;
}

AdaptativeWeighingRouting::AdaptativeWeighingRouting(std::shared_ptr<Topology>
        T, std::vector<std::shared_ptr<PSR::Cost>> Costs) :
    PowerSeriesRouting(T, Costs)
{
    RoutAlgType = AWR;
}
