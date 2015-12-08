#include <RWA/RegeneratorAssignment/FirstLongestReach.h>
#include <Structure/Node.h>

FirstLongestReach::FirstLongestReach(std::shared_ptr<Topology> T,
                                     std::vector<std::shared_ptr<M_QAM>> ModulationSchemes) :
    RegeneratorAssignment(T), ModulationSchemes(ModulationSchemes) {

}

bool FirstLongestReach::assignRegenerators(Call C, std::shared_ptr<Route> R) {
    unsigned int NeededRegenerators = get_NumNeededRegenerators(C);
    auto r = R->Nodes.begin();

    for (auto s = R->Nodes.begin(); s != R->Nodes.end(); ++s) {
        for (auto x = s + 1; s != R->Nodes.end(); ++x) {
            if (((*x).lock()->get_NumAvailableRegenerators() >= NeededRegenerators) ||
                    ((*x).lock() == C.Destination.lock())) {
                if (isThereSpectrumAndOSNR(C, R, *s, *x)) {
                    if ((*x).lock() == C.Destination.lock()) {
                        //It's possible to implement the call.
                        return true;
                    } else {
                        r = x;
                    }
                } else {
                    if (r != s) {
                        R->Regenerators.emplace(*r, NeededRegenerators);
                        s = r;
                        x = r;
                    } else {
                        R->Regenerators.clear();
                        return false;
                    }
                }
            }
        }
    }

    return false;
}

bool FirstLongestReach::isThereSpectrumAndOSNR(Call C,
        std::shared_ptr<Route> R,
        std::weak_ptr<Node> s,
        std::weak_ptr<Node> x) {

    Signal S = R->partial_bypass(s, x);

    for (auto scheme : ModulationSchemes) {
        //There's OSNR
        if (S.get_OSNR() > scheme->get_ThresholdOSNR(C.Bitrate)) {
            //There's spectrum
            if (R->get_MaxContigSlots(s, x) > scheme->get_NumSlots(C.Bitrate)) {
                return true;
            }
        }
    }

    return false;
}
