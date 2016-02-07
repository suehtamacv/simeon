#include "include/RWA/WavelengthAssignmentAlgorithms/ContiguityFit.h"
#include <set>
#include <Calls/Call.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>

ContiguityFit::ContiguityFit(std::shared_ptr<Topology> T) :
    WavelengthAssignmentAlgorithm(T, WavelengthAssignmentAlgorithm::CF)
{

}

std::map<std::weak_ptr<Link>,
    std::vector<std::weak_ptr<Slot>>,
    std::owner_less<std::weak_ptr<Link>>>
    ContiguityFit::assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg)
{

    int RequiredSlots = Seg.ModScheme.get_NumSlots(C->Bitrate);
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;
    Slots.clear();

    bool SlotsAvailability[Link::NumSlots + 1];
    std::set<std::pair<int, int>> InitialSlotsAndHoles;

    for (int i = 0; i < Link::NumSlots; i++)
        {
        SlotsAvailability[i] = true;
        }
    SlotsAvailability[Link::NumSlots] = false;

    for (auto &link : Seg.Links)
        {
        auto locklink = link.lock();

        for (auto &slot : locklink->Slots)
            {
            SlotsAvailability[slot->numSlot] &= slot->isFree;
            }
        }

    int CurrentFreeSlots = 0;

    for (int sf = 0; sf <= Link::NumSlots; sf++)
        {
        if (SlotsAvailability[sf])
            {
            CurrentFreeSlots++;
            }
        else
            {
            if (CurrentFreeSlots != 0 && CurrentFreeSlots >= RequiredSlots)
                {
                InitialSlotsAndHoles.emplace(CurrentFreeSlots, sf - CurrentFreeSlots);
                }
            CurrentFreeSlots = 0;
            }
        }

    if (!InitialSlotsAndHoles.empty())
        {
        int si = InitialSlotsAndHoles.begin()->second;
        for (auto &link : Seg.Links)
            {
            Slots.emplace(link, std::vector<std::weak_ptr<Slot>>
                          (link.lock()->Slots.begin() + si,
                           link.lock()->Slots.begin() + si + RequiredSlots));
            }
        }

    return Slots;
}

void ContiguityFit::save(std::string SimConfigFileName)
{
    WavelengthAssignmentAlgorithm::save(SimConfigFileName);
}
