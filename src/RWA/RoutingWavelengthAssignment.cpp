#include <RWA/RoutingWavelengthAssignment.h>

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm> R_Alg,
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg) :
    R_Alg(R_Alg) , WA_Alg(WA_Alg) {

}

