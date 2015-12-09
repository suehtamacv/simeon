#include <RWA/RegeneratorAssignment/FirstLongestReach.h>
#include <Structure/Node.h>
#include <Structure/Link.h>

FirstLongestReach::FirstLongestReach(std::shared_ptr<Topology> T,
                                     std::vector<std::shared_ptr<ModulationScheme>> ModulationSchemes) :
    RegeneratorAssignment(T, ModulationSchemes) {

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
                        R->Segments.push_back(createTransparentSegment(C, R,
                                              *r, *x, NeededRegenerators));
                        return true;
                    } else {
                        r = x;
                    }
                } else {
                    if (r != s) {
                        R->Segments.push_back(createTransparentSegment(C, R,
                                              *s, *r, NeededRegenerators));
                        R->Regenerators.emplace(*r, NeededRegenerators);
                        s = r;
                        x = r;
                    } else {
                        R->Regenerators.clear();
                        R->Segments.clear();
                        return false;
                    }
                }
            }
        }
    }

    return false;
}
