#include <RWA/RoutingAlgorithms/PowerSeriesRouting/PSRVariants/LocalPowerSeriesRouting.h>

LocalPowerSeriesRouting::LocalPowerSeriesRouting(std::shared_ptr<Topology> T)
    : PowerSeriesRouting(T, localPSR)
{
    Variant = Variant_LocalPSR;
}

LocalPowerSeriesRouting::LocalPowerSeriesRouting
(std::shared_ptr<Topology> T, std::vector<std::shared_ptr<PSR::Cost>> Costs)
    : PowerSeriesRouting(T, Costs, localPSR)
{
    Variant = Variant_LocalPSR;
}

double LocalPowerSeriesRouting::get_Cost
(std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
    return 0;
}
