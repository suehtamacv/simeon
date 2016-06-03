#include <boost/assert.hpp>
#include <Structure/Slot.h>
#include <Structure/Link.h>
#include <GeneralClasses/LinkSpectralDensity.h>
#include <GeneralClasses/PhysicalConstants.h>

Slot::Slot(int numSlot) : numSlot(numSlot), isFree(true)
{
    double centerFreq = PhysicalConstants::freq +
                        BSlot * (numSlot - (Link::NumSlots / 2));
    S = std::make_shared<SpectralDensity>(centerFreq - BSlot / 2.0,
                                          centerFreq + BSlot / 2.0,
                                          (int) numFrequencySamplesPerSlot, true);
}

void Slot::freeSlot()
{
    BOOST_ASSERT_MSG(!isFree, "Only occupied slots can be freed.");
    isFree = true;
    S->specDensity.zeros();
}

void Slot::useSlot()
{
    BOOST_ASSERT_MSG(isFree, "Only free slots can be used.");
    isFree = false;
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
