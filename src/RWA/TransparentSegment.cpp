#include <RWA/TransparentSegment.h>
#include <Structure/Link.h>
#include <Structure/Node.h>
#include <Structure/Topology.h>

TransparentSegment::TransparentSegment(std::vector<std::weak_ptr<Link>> Links,
                                       ModulationScheme ModScheme, unsigned int NumRegUsed) :
    Links(Links), ModScheme(ModScheme), NumRegUsed(NumRegUsed) {

    Nodes.push_back(Links.front().lock()->Origin);

    for (auto it : Links) {
        Nodes.push_back(it.lock()->Destination);
    }

}

TransparentSegment::TransparentSegment(const TransparentSegment &segment) :
    ModScheme(segment.ModScheme) {
    NumRegUsed = segment.NumRegUsed;
    Nodes = segment.Nodes;
    Links = segment.Links;
}

Signal TransparentSegment::bypass(Signal S) {
    S = Links.front().lock()->Origin.lock()->add(S);

    for (auto it : Links) {
        S = it.lock()->bypass(S);

        if (it.lock() == Links.back().lock()) {
            S = it.lock()->Destination.lock()->drop(S);
        } else {
            S = it.lock()->Destination.lock()->bypass(S);
        }
    }

    return S;
}

unsigned int TransparentSegment::get_MaxContigSlots() {

    std::vector<bool> SlotsAvailability(Link::NumSlots, true);

    for (auto link : Links) {
        for (unsigned int i = 0; i < Link::NumSlots; i++) {
            SlotsAvailability[i] = SlotsAvailability[i] &&
                                   link.lock()->isSlotFree(i);
        }
    }

    unsigned MaxSlots = 0;
    unsigned CurrentFreeSlots = 0;

    for (auto slot : SlotsAvailability) {
        if (slot) {
            CurrentFreeSlots++;
        } else {
            CurrentFreeSlots = 0;
        }

        if (CurrentFreeSlots > MaxSlots) {
            MaxSlots = CurrentFreeSlots;
        }
    }

    return MaxSlots;
}

