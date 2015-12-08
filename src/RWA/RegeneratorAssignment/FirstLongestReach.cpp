#include <RWA/RegeneratorAssignment/FirstLongestReach.h>

FirstLongestReach::FirstLongestReach(std::shared_ptr<Topology> T,
                                     std::vector<std::shared_ptr<M_QAM>> ModulationSchemes) :
    RegeneratorAssignment(T), ModulationSchemes(ModulationSchemes) {

}

void FirstLongestReach::assignRegenerators(Call C, std::shared_ptr<Route> R) {

}
