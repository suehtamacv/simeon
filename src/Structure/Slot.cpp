#include <boost/assert.hpp>
#include <Structure/Slot.h>

Slot::Slot(int numSlot, Link *Owner) : numSlot(numSlot) {
    SlotOwner = Owner;
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
