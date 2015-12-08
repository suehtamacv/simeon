#ifndef SLOT_H
#define SLOT_H

#include <memory>

class Link;

class Slot {
  public:
    /**
     * @brief BSlot is the bandwidth of a single slot.
     */
    constexpr static long double BSlot = 12.5E9;

	Slot(int, Link* Owner);

	/**
	 * @brief numSlot identifies the slot in the link.
	 */
	int numSlot;
	/**
	 * @brief isFree is true, iff the slot is free.
	 */
	bool isFree;

	void freeSlot();
	void useSlot();
	Link* SlotOwner;
};

#endif // SLOT_H
