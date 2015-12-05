#include <RWA/RoutingWavelengthAssignment.h>

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm> R_Alg,
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg) , WA_Alg(WA_Alg) , T(T) {

}

std::shared_ptr<Route> RoutingWavelengthAssignment::routeCall(Call C) {
    std::vector<std::weak_ptr<Link>> Links = R_Alg->route(C);
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>> Slots =
        WA_Alg->assignSlots(C, Links);

    return std::shared_ptr<Route>(new Route(Links, Slots));
}
