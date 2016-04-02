#include <RMSA/SpectrumAssignmentAlgorithms/FirstFit.h>
#include <Calls/Call.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>

using namespace SA;

FirstFit::FirstFit(std::shared_ptr<Topology> T) :
    SpectrumAssignmentAlgorithm(T, SpectrumAssignmentAlgorithms::FF)
{

}

std::map<std::weak_ptr<Link>,
    std::vector<std::weak_ptr<Slot>>,
    std::owner_less<std::weak_ptr<Link>>>
    FirstFit::assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg)
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

    int CurrentFreeSlots = 0;
    int si = -1, sf = 0;

    for (sf = 0; sf < Link::NumSlots; sf++)
        {
        if (SlotsAvailability[sf])
            {
            CurrentFreeSlots++;
            }
        else
            {
            CurrentFreeSlots = 0;
            }

        if (CurrentFreeSlots == RequiredSlots)
            {
            si = sf - RequiredSlots + 1;
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

void FirstFit::save(std::string SimConfigFileName)
{
    SpectrumAssignmentAlgorithm::save(SimConfigFileName);
}
