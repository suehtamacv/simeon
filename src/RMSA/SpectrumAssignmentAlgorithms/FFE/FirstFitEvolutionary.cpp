#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FirstFitEvolutionary.h"
#include <Structure/Topology.h>
#include <Calls/Call.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <algorithm>

using namespace RMSA::SA;
using namespace RMSA::SA::FFE;

bool FirstFitEvolutionary::hasLoaded = false;
bool FirstFitEvolutionary::hasCreatedDefaultList = false;
std::vector<int> FirstFitEvolutionary::defaultSlotsList(Link::NumSlots);

FirstFitEvolutionary::FirstFitEvolutionary(std::shared_ptr<Topology> T) :
    SpectrumAssignmentAlgorithm(T, FFE)
{
    if (!hasCreatedDefaultList)
        {
        std::iota(defaultSlotsList.begin(), defaultSlotsList.end(), 0);
        hasCreatedDefaultList = true;
        }

    slotsList = defaultSlotsList;
}

void FirstFitEvolutionary::save(std::string filename)
{
    SpectrumAssignmentAlgorithm::save(filename);
}

std::map<std::weak_ptr<Link>,
    std::vector<std::weak_ptr<Slot>>,
    std::owner_less<std::weak_ptr<Link>>>
    FirstFitEvolutionary::assignSlots
    (std::shared_ptr<Call> C, TransparentSegment Seg)
{
    int RequiredSlots = Seg.ModScheme.get_NumSlots(C->Bitrate);
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;
    Slots.clear();

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

    for (auto si : slotsList)
        {
        if (si + RequiredSlots - 1 >= Link::NumSlots)
            {
            continue;
            }

        bool freeSlots = true;
        for (int s = si; (s < si + RequiredSlots) && freeSlots; ++s)
            {
            freeSlots &= SlotsAvailability[s];
            }

        if (freeSlots)
            {
            for (auto &link : Seg.Links)
                {
                Slots.emplace(link, std::vector<std::weak_ptr<Slot>>
                              (link.lock()->Slots.begin() + si,
                               link.lock()->Slots.begin() + si + RequiredSlots));
                }
            break;
            }
        }

    return Slots;
}
