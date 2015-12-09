#include <RWA/WavelengthAssignment/FirstFit.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>

FirstFit::FirstFit(std::shared_ptr<Topology> T,
                   std::vector<ModulationScheme> Schemes) :
    WavelengthAssignmentAlgorithm(T, Schemes) {

}
