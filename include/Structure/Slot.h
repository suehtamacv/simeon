#ifndef SLOT_H
#define SLOT_H

#include <memory>

class Link;

class Slot {
  public:
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
