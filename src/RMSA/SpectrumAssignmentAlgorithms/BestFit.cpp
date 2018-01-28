#include "include/RMSA/SpectrumAssignmentAlgorithms/BestFit.h"
#include <set>
#include <Calls/Call.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>

using namespace RMSA::SA;

BestFit::BestFit(std::shared_ptr<Topology> T) :
    SpectrumAssignmentAlgorithm(T, SpectrumAssignmentAlgorithm::BF)
{

}

mapSlots BestFit::assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg)
{

    int RequiredSlots = Seg.ModScheme.get_NumSlots(C->Bitrate);
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;
    Slots.clear();

    bool SlotsAvailability[Link::NumSlots + 1];
    std::set<std::pair<int, int>> PossibleBlocks;

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
                PossibleBlocks.emplace(CurrentFreeSlots, sf - CurrentFreeSlots);
                }
            CurrentFreeSlots = 0;
            }
        }

    if (!PossibleBlocks.empty())
        {
        int si = PossibleBlocks.begin()->second;
        for (auto &link : Seg.Links)
            {
            Slots.emplace(link, std::vector<std::weak_ptr<Slot>>
                          (link.lock()->Slots.begin() + si,
                           link.lock()->Slots.begin() + si + RequiredSlots));
            }
        }

    return Slots;
}

void BestFit::save(std::string SimConfigFileName)
{
    SpectrumAssignmentAlgorithm::save(SimConfigFileName);
}
