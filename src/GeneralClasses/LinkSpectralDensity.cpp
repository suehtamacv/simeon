#include <GeneralClasses/LinkSpectralDensity.h>

#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>

unsigned long LinkSpectralDensity::numFrequencySamples =
    Slot::numFrequencySamplesPerSlot * Link::NumSlots;

LinkSpectralDensity::LinkSpectralDensity(std::vector<std::shared_ptr<Slot>>
        LinkSlots) : LinkSlots(LinkSlots)
{

}

