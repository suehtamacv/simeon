#include "GeneralClasses/LinkSpectralDensity.h"

#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>

unsigned long LinkSpectralDensity::numFrequencySamples =
    LinkSpectralDensity::numFrequencySamplesPerSlot * Link::NumSlots;

LinkSpectralDensity::LinkSpectralDensity()
{
    double frequencyRange = Link::NumSlots * Slot::BSlot / 2;

    double freqStep = PhysicalConstants::freq - frequencyRange;
    for(unsigned int i = 0; i < (int) numFrequencySamples; i++)
    {
        frequencyValues.push_back(freqStep);
        freqStep += frequencyRange * 2 / numFrequencySamples;
    }

    S = std::make_shared<SpectralDensity>(PhysicalConstants::freq -
                                          frequencyRange, PhysicalConstants::freq + frequencyRange,
                                          (int) numFrequencySamples);

    X = std::make_shared<SpectralDensity>(PhysicalConstants::freq -
                                          frequencyRange, PhysicalConstants::freq + frequencyRange,
                                          (int) numFrequencySamples);
}
