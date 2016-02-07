#include "include/RWA/WavelengthAssignmentAlgorithms/RandomFit.h"
#include <GeneralClasses/RandomGenerator.h>
#include <Calls/Call.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>

RandomFit::RandomFit(std::shared_ptr<Topology> T) :
    WavelengthAssignmentAlgorithm(T, WavelengthAssignmentAlgorithms::RF)
{

}

std::map<std::weak_ptr<Link>,
    std::vector<std::weak_ptr<Slot>>,
    std::owner_less<std::weak_ptr<Link>>>
    RandomFit::assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg)
{
    unsigned int RequiredSlots = Seg.ModScheme.get_NumSlots(C->Bitrate);
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;
    std::vector<int> PossibleLastSlots;

    bool SlotsAvailability[Link::NumSlots];

    for (int i = 0; i < Link::NumSlots; i++)
        {
        SlotsAvailability[i] = true;
        }

    for (auto &link : Seg.Links)
        {
        auto locklink = link.lock();

        for (auto &slot : locklink->Slots)
            {
            SlotsAvailability[slot->numSlot] &= slot->isFree;
            }
        }

    unsigned int CurrentFreeSlots = 0;

    for (int sf = 0; sf < Link::NumSlots; sf++)
        {
        if (SlotsAvailability[sf])
            {
            CurrentFreeSlots++;
            }
        else
            {
            CurrentFreeSlots = 0;
            }

        if (CurrentFreeSlots >= RequiredSlots)
            {
            PossibleLastSlots.push_back(sf);
            }
        }

    if (!PossibleLastSlots.empty())
        {
        std::uniform_int_distribution<int> SlotChoose(0, PossibleLastSlots.size() - 1);
        auto SF = PossibleLastSlots.begin();
        std::advance(SF, SlotChoose(random_generator));

        for (auto &link : Seg.Links)
            {
            Slots.emplace(link, std::vector<std::weak_ptr<Slot>>
                          (link.lock()->Slots.begin() + *SF - RequiredSlots + 1,
                           link.lock()->Slots.begin() + *SF + 1));
            }
        }

    return Slots;
}

void RandomFit::save(std::string SimConfigFileName)
{
    WavelengthAssignmentAlgorithm::save(SimConfigFileName);
}
