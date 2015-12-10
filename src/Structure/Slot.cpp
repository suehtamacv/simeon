#include <boost/assert.hpp>
#include <Structure/Slot.h>

Slot::Slot(int numSlot) : numSlot(numSlot) {
    isFree = true;
}

void Slot::freeSlot() {
    BOOST_ASSERT_MSG(!isFree, "Only occupied slots can be freed.");
    isFree = true;
}

void Slot::useSlot() {
    BOOST_ASSERT_MSG(isFree, "Only free slots can be used.");
    isFree = false;
}

Slot::Slot(const Slot &slot) {
    numSlot = slot.numSlot;
    isFree = slot.isFree;
}

Slot &Slot::operator =(const Slot &slot) {
    if (this != &slot) {
        numSlot = slot.numSlot;
        isFree = slot.isFree;
    }

    return *this;
}
