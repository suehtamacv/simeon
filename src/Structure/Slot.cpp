#include <boost/assert.hpp>
#include <Structure/Slot.h>

#include <GeneralClasses/LinkSpectralDensity.h>
#include <Structure/Link.h>
#include <GeneralClasses/PhysicalConstants.h>

Slot::Slot(int numSlot) : numSlot(numSlot), isFree(true),
    firstPos((unsigned int) numFrequencySamplesPerSlot * (numSlot - 1)),
    lastPos((unsigned int) numFrequencySamplesPerSlot * numSlot - 1)
{
    double frequencyRange = Link::NumSlots * BSlot / 2;
    double freqStep = PhysicalConstants::freq - frequencyRange;
    for(unsigned int i = 0; i < (unsigned int) numFrequencySamplesPerSlot; i++)
        {
        frequencyValues.push_back(freqStep);
        freqStep += frequencyRange * 2 / LinkSpectralDensity::numFrequencySamples;
        }
    S = std::make_shared<SpectralDensity>(PhysicalConstants::freq -
                                          frequencyRange, PhysicalConstants::freq + frequencyRange,
                                          (int) numFrequencySamplesPerSlot, true);
}

void Slot::freeSlot()
{
    BOOST_ASSERT_MSG(!isFree, "Only occupied slots can be freed.");
    isFree = true;

    for(unsigned int i = 0; i <= (unsigned int) numFrequencySamplesPerSlot - 1; i++)
        {
        S->specDensity(i) = 0;
        }
}

void Slot::useSlot()
{
    BOOST_ASSERT_MSG(isFree, "Only free slots can be used.");
    isFree = false;



    /*
    for(unsigned int i = 0; i <= (unsigned int) numFrequencySamplesPerSlot - 1; i++)
        {
        double freqVal = frequencyValues.at(i);
        S->specDensity(i) = std::exp2l( (-2) * pow( 2 * (freqVal -
                                        PhysicalConstants::freq) / SpectralDensity::SBW_3dB,
                                        2 * SpectralDensity::TxFilterOrder));
        }
    */
}

Slot::Slot(const Slot &slot)
{
    numSlot = slot.numSlot;
    isFree = slot.isFree;
}

Slot &Slot::operator =(const Slot &slot)
{
    if (this != &slot)
        {
        numSlot = slot.numSlot;
        isFree = slot.isFree;
        }

    return *this;
}
