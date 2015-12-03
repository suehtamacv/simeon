#include <cassert>
#include <Structure/Slot.h>

Slot::Slot(int numSlot, Link *Owner) : numSlot(numSlot) {
    SlotOwner = Owner;
    isFree = true;
}

void Slot::freeSlot() {
    assert(!isFree);
    isFree = true;
}

void Slot::useSlot() {
    assert(isFree);
    isFree = false;
}
