#include <Structure/Slot.h>
#include <gtest/gtest.h>

Slot::Slot(int numSlot) : numSlot(numSlot), isFree(true)
{

}

void Slot::freeSlot()
{
    EXPECT_FALSE(isFree) << "Only occupied slots can be freed.";
    isFree = true;
}

void Slot::useSlot()
{
    EXPECT_TRUE(isFree) << "Only free slots can be used.";
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
