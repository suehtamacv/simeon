#include <GeneralClasses/LinkSpectralDensity.h>

#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h>

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

Power LinkSpectralDensity::get_TransmitedPower(double frequencyRange)
{
    SpectralDensity originSD(PhysicalConstants::freq - frequencyRange,
                             PhysicalConstants::freq + frequencyRange,
                             Slot::numFrequencySamplesPerSlot);

    Power tPower = Power(NumericMethods::TrapezoidalRule(originSD.specDensity,
                                         frequencyRange * 2).calculate() * originSD.densityScaling, Power::Watt);
    return tPower;
}

void LinkSpectralDensity::updateLink(SpectralDensity thisSpecDensity,std::vector<std::weak_ptr<Slot>> Slots)
{

    unsigned int firstSlot = Slots.front().lock()->numSlot;
    unsigned int lastSlot = Slots.back().lock()->numSlot;

    unsigned int k = 0;
    for(unsigned int i = firstSlot - 1; i < lastSlot; i++) // Talvez i = firstSlot, a testar isso
    {
        for(unsigned int j = 0; j < Slot::numFrequencySamplesPerSlot; j++)
        {
            S.at(i)->specDensity(j) = thisSpecDensity.specDensity(k);
            k++;
        }
        LinkSlots.at(i)->S = S.at(i);
    }

}
