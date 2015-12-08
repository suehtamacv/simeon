#include <RWA/RoutingWavelengthAssignment.h>

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm> R_Alg,
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
    std::shared_ptr<RegeneratorPlacement> RP_Alg,
    std::shared_ptr<RegeneratorAssignment> RA_Alg,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), RP_Alg(RP_Alg), RA_Alg(RA_Alg), T(T) {

}

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm>  R_Alg,
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), T(T) {

    RP_Alg = 0;
    RA_Alg = 0;

}

std::shared_ptr<Route> RoutingWavelengthAssignment::routeCall(Call C) {

    if (RA_Alg != 0) {
        //No algorithm RA. Transparent Network.
        std::vector<std::weak_ptr<Link>> Links = R_Alg->route(C);
        std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>> Slots =
            WA_Alg->assignSlots(C, Links);

        return std::shared_ptr<Route>(new Route(Links, Slots));
    } else {
        //There's an RA Algorithm.
    }
}
