#include <GeneralClasses/LinkSpectralDensity.h>

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

void LinkSpectralDensity::updateLink(SpectralDensity thisSpecDensity,std::vector<std::weak_ptr<Slot>> Slots)
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
