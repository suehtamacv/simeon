#include <GeneralClasses/LinkSpectralDensity.h>

#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>

unsigned long LinkSpectralDensity::numFrequencySamples =
    Slot::numFrequencySamplesPerSlot * Link::NumSlots;

LinkSpectralDensity::LinkSpectralDensity(std::vector<std::shared_ptr<Slot>>
        LinkSlots) : LinkSlots(LinkSlots)
{
    for(auto& slot : LinkSlots)
    {
        S.push_back(slot->S);
        X.push_back(slot->X);
    }
}

Power LinkSpectralDensity::get_SpectralPower()
{
    Power teste(0, Power::Watt);
    return teste;
}
