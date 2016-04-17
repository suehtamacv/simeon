#include <GeneralClasses/LinkSpectralDensity.h>

#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>

unsigned long LinkSpectralDensity::numFrequencySamples =
    LinkSpectralDensity::numFrequencySamplesPerSlot * Link::NumSlots;

LinkSpectralDensity::LinkSpectralDensity()
{
    double frequencyRange = Link::NumSlots * Slot::BSlot / 2;

    double freqStep = PhysicalConstants::freq - frequencyRange;
    for(unsigned int i = 0; i < (unsigned int) numFrequencySamples; i++)
        {
        frequencyValues.push_back(freqStep);
        freqStep += frequencyRange * 2 / numFrequencySamples;
        }

    S = std::make_shared<SpectralDensity>(PhysicalConstants::freq -
                                          frequencyRange, PhysicalConstants::freq + frequencyRange,
                                          (int) numFrequencySamples, true);

    X = std::make_shared<SpectralDensity>(PhysicalConstants::freq -
                                          frequencyRange, PhysicalConstants::freq + frequencyRange,
                                          (int) numFrequencySamples, true);

    unsigned int firstPos, lastPos;
    for(unsigned int i = 1; i <= (unsigned int) Link::NumSlots; i++)
        {
        firstPos = (int) numFrequencySamplesPerSlot * (i - 1);
        lastPos = (int) numFrequencySamplesPerSlot * i - 1;
        slotsPositionsMap.emplace(i, std::make_pair(firstPos, lastPos));
        }
}

void LinkSpectralDensity::setSlot(int numSlot)
{
    std::pair<unsigned int, unsigned int> slotPos = slotsPositionsMap.at(numSlot);
    for(unsigned int i = slotPos.first; i <= slotPos.second; i++)
        {
        double freqVal = frequencyValues.at(i);
        S->specDensity(i) = std::exp2l( (-2) * pow( 2 * (freqVal -
                                        PhysicalConstants::freq) / SpectralDensity::SBW_3dB,
                                        2 * SpectralDensity::TxFilterOrder));
        X->specDensity(i) = 0;
        }
}

void LinkSpectralDensity::clearSlot(int numSlot)
{
    std::pair<unsigned int, unsigned int> slotPos = slotsPositionsMap.at(numSlot);
    for(unsigned int i = slotPos.first; i <= slotPos.second; i++)
        {
        S->specDensity(i) = 0;
        X->specDensity(i) = 0;
        }
}
