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

}
