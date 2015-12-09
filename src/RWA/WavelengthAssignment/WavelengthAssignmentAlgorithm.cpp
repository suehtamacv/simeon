#include <RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.h>

WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithm(
    std::shared_ptr<Topology> T, std::vector<ModulationScheme> Schemes)
    : T(T), Schemes(Schemes) {

}

