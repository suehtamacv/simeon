#include <algorithm>
#include <RWA/RoutingWavelengthAssignment.h>

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm> R_Alg,
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
    std::shared_ptr<RegeneratorPlacement> RP_Alg,
    std::shared_ptr<RegeneratorAssignment> RA_Alg,
    std::vector<ModulationScheme> Schemes,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), RP_Alg(RP_Alg),
    RA_Alg(RA_Alg), Schemes(Schemes), T(T) {

}

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm>  R_Alg,
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
    std::vector<ModulationScheme> Schemes,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), Schemes(Schemes), T(T) {

    RP_Alg = 0;
    RA_Alg = 0;

}

std::shared_ptr<Route> RoutingWavelengthAssignment::routeCall(Call C) {

    std::vector<std::weak_ptr<Link>> Links = R_Alg->route(C);

    if (RA_Alg == 0) {
        //No algorithm RA. Transparent Network.
        std::sort(Schemes.rbegin(), Schemes.rend());
    } else {
        //There's an RA Algorithm.
    }
}
