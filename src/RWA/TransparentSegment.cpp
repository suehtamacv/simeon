#include <RWA/TransparentSegment.h>
#include <Structure/Link.h>
#include <Structure/Node.h>
#include <Structure/Topology.h>

TransparentSegment::TransparentSegment(std::vector<std::weak_ptr<Link>> Links,
                                       ModulationScheme ModScheme, unsigned int NumRegUsed) :
    Links(Links), ModScheme(ModScheme), NumRegUsed(NumRegUsed) {

    for (auto it : Links) {
        if (it.lock() == Links.front().lock()) {
            Nodes.push_back(it.lock()->Origin);
        }

        Nodes.push_back(it.lock()->Destination);
    }

}

Signal TransparentSegment::bypass(Signal S) {
    for (auto it : Links) {
        if (it.lock() == Links.front().lock()) {
            S = it.lock()->Origin.lock()->add(S);
        }

        S = it.lock()->bypass(S);

        if (it.lock() == Links.back().lock()) {
            S = it.lock()->Destination.lock()->drop(S);
        }
    }

    return S;
}
