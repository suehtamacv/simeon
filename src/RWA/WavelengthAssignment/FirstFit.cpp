#include <RWA/WavelengthAssignment/FirstFit.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>

FirstFit::FirstFit(std::shared_ptr<Topology> T) :
    WavelengthAssignmentAlgorithm(T) {

}

std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>>
FirstFit::assignSlots(Call C, std::vector<std::weak_ptr<Link>> Links) {

    bool AvailableSlots[Link::NumSlots];

    for (int i = 0; i < Link::NumSlots; i++) {
        AvailableSlots[i] = true;
    }


}

