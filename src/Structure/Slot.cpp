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
                                          (int) samplesPerSlot, true);
}

void Slot::freeSlot()
{
#ifdef RUN_ASSERTIONS
    if (isFree)
        {
        std::cerr << "Only occupied slots can be freed." << std::endl;
        abort();
        }
#endif
    isFree = true;
    S->specDensity.zeros();
}

void Slot::useSlot()
{
#ifdef RUN_ASSERTIONS
    if (!isFree)
        {
        std::cerr << "Only occupied slots can be used." << std::endl;
        abort();
        }
#endif
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
