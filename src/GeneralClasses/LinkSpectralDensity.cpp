#include <GeneralClasses/LinkSpectralDensity.h>
#include <boost/assert.hpp>
#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h>
#include <GeneralClasses/SpectralDensity.h>

unsigned long LinkSpectralDensity::numFrequencySamples =
    Slot::numFrequencySamplesPerSlot * Link::NumSlots;

LinkSpectralDensity::LinkSpectralDensity(std::vector<std::shared_ptr<Slot>>
        LinkSlots) : LinkSlots(LinkSlots)
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
        for(unsigned int j = 0; j < Slot::numFrequencySamplesPerSlot; j++)
            {
            S.at(i)->specDensity(j) = thisSpecDensity.specDensity(k);
            k++;
            }
        LinkSlots.at(i)->S = S.at(i);
        }
}

std::shared_ptr<SpectralDensity> LinkSpectralDensity::slice(
    unsigned initialSlot,
    unsigned finalSlot)
{
    BOOST_ASSERT_MSG(finalSlot < S.size() - 1, "Invalid slot requested.");

    int numSlots = finalSlot - initialSlot + 1;
    double frequencyRange = numSlots * Slot::BSlot / 2;
    std::shared_ptr<SpectralDensity> PSD = std::make_shared<SpectralDensity>
                                           (PhysicalConstants::freq - frequencyRange,
                                            PhysicalConstants::freq + frequencyRange,
                                            Slot::numFrequencySamplesPerSlot * numSlots, true);

    for (int s = 0; s < numSlots; s++)
        {
        PSD->specDensity.cols(s * Slot::numFrequencySamplesPerSlot,
                              (s + 1) * Slot::numFrequencySamplesPerSlot - 1) =
                                  S.at(initialSlot + s)->specDensity;
        }

    return PSD;
}