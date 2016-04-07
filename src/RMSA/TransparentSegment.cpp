#include <RMSA/TransparentSegment.h>
#include <Structure/Link.h>
#include <Structure/Node.h>
#include <Structure/Topology.h>
#include <Calls/Call.h>

using namespace RMSA;

TransparentSegment::TransparentSegment(std::vector<std::weak_ptr<Link>> Links,
                                       ModulationScheme ModScheme, unsigned int NumRegUsed) :
    Links(Links), ModScheme(ModScheme), NumRegUsed(NumRegUsed)
{

    Nodes.push_back(Links.front().lock()->Origin);

    for (auto &it : Links)
        {
        Nodes.push_back(it.lock()->Destination);
        }

}

TransparentSegment::TransparentSegment(const TransparentSegment &segment) :
    ModScheme(segment.ModScheme)
{
    NumRegUsed = segment.NumRegUsed;
    Nodes = segment.Nodes;
    Links = segment.Links;
}

Signal TransparentSegment::bypass(Signal S)
{
    S = Links.front().lock()->Origin.lock()->add(S);

    for (auto &it : Links)
        {
        S = it.lock()->bypass(S);

        if (it.lock() == Links.back().lock())
            {
            S = it.lock()->Destination.lock()->drop(S);
            }
        else
            {
            S = it.lock()->Destination.lock()->bypass(S);
            }
        }

    return S;
}

unsigned int TransparentSegment::get_MaxContigSlots()
{

    std::vector<bool> SlotsAvailability(Link::NumSlots, true);

    for (auto &link : Links)
        {
        auto linklock = link.lock();

        for (int i = 0; i < Link::NumSlots; i++)
            {
            SlotsAvailability[i] = SlotsAvailability[i] &&
                                   linklock->isSlotFree(i);
            }
        }

    unsigned MaxSlots = 0;
    unsigned CurrentFreeSlots = 0;

    for (bool slot : SlotsAvailability)
        {
        if (slot)
            {
            CurrentFreeSlots++;
            }
        else
            {
            CurrentFreeSlots = 0;
            }

        if (CurrentFreeSlots > MaxSlots)
            {
            MaxSlots = CurrentFreeSlots;
            }
        }

    return MaxSlots;
}

int TransparentSegment::get_Contiguity(std::shared_ptr<Call> C)
{
    int NumRequiredSlots = ModScheme.get_NumSlots(C->Bitrate);
    int Contiguity = 0;
    int CurrentFreeSlots = 0;

    auto Slots = std::vector<bool>(Link::NumSlots, true);
    for (auto &link : Links)
        {
        for (unsigned i = 0; i < Slots.size(); ++i)
            {
            Slots[i] = Slots[i] && link.lock()->isSlotFree(i);
            }
        }

    for (int s = 0; s < Link::NumSlots; s++)
        {
        if (Slots[s])
            {
            CurrentFreeSlots++;
            }
        else
            {
            CurrentFreeSlots = 0;
            }

        if (CurrentFreeSlots >= NumRequiredSlots)
            {
            Contiguity++;
            }
        }

    return Contiguity;
}
