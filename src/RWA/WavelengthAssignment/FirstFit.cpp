#include <RWA/WavelengthAssignment/FirstFit.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>

FirstFit::FirstFit(std::shared_ptr<Topology> T) :
    WavelengthAssignmentAlgorithm(T) {

}

std::map<std::weak_ptr<Link>,
    std::vector<std::weak_ptr<Slot>>,
    std::owner_less<std::weak_ptr<Link>>>
FirstFit::assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg) {

    unsigned int RequiredSlots = Seg.ModScheme.get_NumSlots(C->Bitrate);
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;
    Slots.clear();

    bool SlotsAvailability[Link::NumSlots];

    for (int i = 0; i < Link::NumSlots; i++) {
        SlotsAvailability[i] = true;
    }

    for (auto link : Seg.Links) {
        for (auto slot : link.lock()->Slots) {
            SlotsAvailability[slot->numSlot] &= slot->isFree;
        }
    }

    unsigned int CurrentFreeSlots = 0;
    int si = -1, sf = 0;

    for (int i = 0; i < Link::NumSlots; i++) {
        if (SlotsAvailability[i]) {
            CurrentFreeSlots++;
        } else {
            CurrentFreeSlots = 0;
        }

        if (CurrentFreeSlots == RequiredSlots) {
            si = sf - RequiredSlots + 1;
            break;
        }

        sf++;
    }

    if (si != -1) {
        for (auto link : Seg.Links) {
            std::vector<std::weak_ptr<Slot>> LinkSlots;

            for (int slot = si; slot <= sf; slot++) {
                LinkSlots.push_back(link.lock()->Slots.at(slot));
            }

            Slots.emplace(link, LinkSlots);
        }
    }

    return Slots;
}
