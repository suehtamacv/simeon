#include <GeneralClasses/LinkSpectralDensity.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h>
#include <GeneralClasses/SpectralDensity.h>

unsigned long LinkSpectralDensity::numFrequencySamples =
    Slot::samplesPerSlot * Link::NumSlots;

LinkSpectralDensity::LinkSpectralDensity
(std::vector<std::shared_ptr<Slot>> LinkSlots) : LinkSlots(LinkSlots)
{
    for(auto& slot : LinkSlots)
        {
        S.push_back(slot->S);
        }
}

void LinkSpectralDensity::updateLink(SpectralDensity thisSpecDensity,
                                     std::vector<std::weak_ptr<Slot>> Slots)
{
    unsigned int firstSlot = Slots.front().lock()->numSlot;
    unsigned int lastSlot = Slots.back().lock()->numSlot;

    unsigned int k = 0;
    for(unsigned int i = firstSlot; i <= lastSlot; i++)
        {
        S.at(i)->densityScaling = thisSpecDensity.densityScaling;
        for(unsigned int j = 0; j < Slot::samplesPerSlot; j++)
            {
            S.at(i)->specDensity(j) = thisSpecDensity.specDensity(k);
            k++;
            }
        LinkSlots.at(i)->S = S.at(i);
        }
}

std::shared_ptr<SpectralDensity> LinkSpectralDensity::slice(
    std::vector<std::weak_ptr<Slot>> usedSlots)
{
    std::sort(usedSlots.begin(), usedSlots.end(),
              [](const std::weak_ptr<Slot> &l, const std::weak_ptr<Slot> &r)
        {
        return l.lock()->numSlot < r.lock()->numSlot;
        });

    int numSlots = usedSlots.size();
    double freqMin = usedSlots.front().lock()->S->freqMin;
    double freqMax = usedSlots.back().lock()->S->freqMax;

#ifdef RUN_ASSERTIONS
    if (freqMax - freqMin != numSlots * Slot::BSlot)
        {
        std::cerr << "Slots are not contiguous" << std::endl;
        abort();
        }
#endif

    std::shared_ptr<SpectralDensity> PSD = std::make_shared<SpectralDensity>
                                           (freqMin, freqMax, Slot::samplesPerSlot * numSlots, true);

    for (int s = 0; s < numSlots; s++)
        {
        PSD->specDensity.cols(s * Slot::samplesPerSlot, (s + 1) * Slot::samplesPerSlot - 1)
            = S.at(usedSlots[s].lock()->numSlot)->specDensity;
        }

    return PSD;
}
