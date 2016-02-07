#include "include/RWA/WavelengthAssignmentAlgorithms/ContiguityFit.h"
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

    bool SlotsAvailability[Link::NumSlots];
    std::vector<int> SpectralHoleSize(1, 0);

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
    int si = -1, sf = 0;

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
        SpectralHoleSize.push_back(CurrentFreeSlots);
        }

    SpectralHoleSize.push_back(0);
    //Forms a sequence of the form 0 1 2 0 1 2 3 0 1 0 0, where the first and last
    //zeros are always there, and serve to easy the search of a objective subsequence.
    //The objective is to find a subsequence of the form 0 1 2 ... NRequiredSlots 0,
    //that is, a hole with exactly NRequiredSlots. If such hole doesn't exists, then
    //holes bigger and bigger are searched

    for (int holeSize = RequiredSlots; holeSize <= Link::NumSlots; ++holeSize)
        {
        std::vector<int> Hole(holeSize + 2, 0);
        std::iota(Hole.begin() + 1, Hole.end() - 1, 1);

        auto SFIterator = std::search(SpectralHoleSize.begin(), SpectralHoleSize.end(),
                                      Hole.begin(), Hole.end());

        if (SFIterator != SpectralHoleSize.end())
            {
            si = (SFIterator - SpectralHoleSize.begin());
            sf = si + RequiredSlots - 1;
            break;
            }
        }

    if (si != -1)
        {
        BOOST_ASSERT_MSG(sf == si + RequiredSlots - 1,
                         "Error in Wavelength Assingment");
        for (auto &link : Seg.Links)
            {
            Slots.emplace(link, std::vector<std::weak_ptr<Slot>>
                          (link.lock()->Slots.begin() + si,
                           link.lock()->Slots.begin() + sf + 1));
            }
        }

    return Slots;
}

void ContiguityFit::save(std::string SimConfigFileName)
{
    WavelengthAssignmentAlgorithm::save(SimConfigFileName);
}
