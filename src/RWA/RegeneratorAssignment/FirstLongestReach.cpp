#include <RWA/RegeneratorAssignment/FirstLongestReach.h>
#include <Structure/Node.h>

FirstLongestReach::FirstLongestReach(std::shared_ptr<Topology> T,
                                     std::vector<std::shared_ptr<M_QAM>> ModulationSchemes) :
    RegeneratorAssignment(T), ModulationSchemes(ModulationSchemes) {

}

bool FirstLongestReach::assignRegenerators(Call C, std::shared_ptr<Route> R) {
    unsigned int NeededRegenerators = get_NumNeededRegenerators(C);

    for (auto s = R->Nodes.begin(); s != R->Nodes.end(); ++s) {
        for (auto x = s + 1; s != R->Nodes.end(); ++x) {
            if (((*x).lock()->get_NumAvailableRegenerators() >= NeededRegenerators) ||
                    ((*x).lock() == C.Destination.lock())) {

            }
        }
    }

    return false;
}

bool FirstLongestReach::isThereSpectrumAndOSNR(Call C,
        std::shared_ptr<Route> R,
        std::vector<std::weak_ptr<Node> >::iterator s,
        std::vector<std::weak_ptr<Node> >::iterator x) {

    Signal S = R->partial_bypass(*s, *x);

}
