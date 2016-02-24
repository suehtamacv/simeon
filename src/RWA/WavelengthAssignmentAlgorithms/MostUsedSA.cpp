#include "include/RWA/WavelengthAssignmentAlgorithms/MostUsedSA.h"
#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <Structure/Topology.h>
#include <Calls/Call.h>

using namespace WA;

MostUsed::MostUsed(std::shared_ptr<Topology> T) :
    WavelengthAssignmentAlgorithm(T, MU)
{

}

std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
    std::owner_less<std::weak_ptr<Link>>>
    MostUsed::assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg)
{
    int RequiredSlots = Seg.ModScheme.get_NumSlots(C->Bitrate);
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;
    Slots.clear();

    std::vector<bool> SlotsAvailability(Link::NumSlots, true);
    std::vector<int> SlotsUsage(Link::NumSlots, -1);

    for (auto &link : Seg.Links)
        {
        auto locklink = link.lock();

        for (auto &slot : locklink->Slots)
            {
            SlotsAvailability[slot->numSlot] = SlotsAvailability[slot->numSlot]
                                               && slot->isFree;
            }
        }

    //Computes in how many links is the s-th slot used.
    for (int s = 0; s < Link::NumSlots; s++)
        {
        if (!SlotsAvailability[s])
            {
            continue;
            }

        SlotsUsage[s] = 0;
        for (auto &link : T->Links)
            {
            SlotsUsage[s] += (int) !link.second->isSlotFree(s);
            }
        }

    int si = -1;

    do
        {
        auto possibleInitSlot = std::distance(SlotsUsage.begin(),
                                              std::max_element(SlotsUsage.begin(), SlotsUsage.end()));

        //There are no available slots
        if (SlotsUsage[possibleInitSlot] == -1)
            {
            break;
            }

        //There aren't enough slots after this slot to accomodate the requisition
        if (possibleInitSlot + RequiredSlots - 1 > Link::NumSlots)
            {
            SlotsUsage[possibleInitSlot] = -1;
            continue;
            }

        //Verifies whether the next slots are all available
        bool validSlot = true;
        for (int s = possibleInitSlot; s < possibleInitSlot + RequiredSlots; ++s)
            {
            validSlot &= SlotsAvailability[s];
            if (!validSlot)
                {
                break;
                }
            }

        if (validSlot)
            {
            si = possibleInitSlot;
            }
        else
            {
            SlotsUsage[possibleInitSlot] = -1;
            }
        }
    while (si == -1);

    if (si != -1)
        {
        for (auto &link : Seg.Links)
            {
            Slots.emplace(link, std::vector<std::weak_ptr<Slot>>
                          (link.lock()->Slots.begin() + si,
                           link.lock()->Slots.begin() + si + RequiredSlots));
            }
        }

    return Slots;
}

void MostUsed::save(std::string SimConfigFileName)
{
    WavelengthAssignmentAlgorithm::save(SimConfigFileName);
}
