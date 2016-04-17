#ifndef SLOT_H
#define SLOT_H

#include <memory>
#include <vector>

class Link;

/**
 * @brief The Slot class represents a frequency slot.
 */
class Slot
{
public:
    /**
     * @brief BSlot is the bandwidth of a single slot.
     */
    constexpr static double BSlot = 12.5E9;

    /**
     * @brief Slot is the standard constructor of a slot.
     */
    Slot(int);
    /**
     * @brief Slot is the copy constructor of a slot.
     */
    Slot(const Slot &slot);

    Slot &operator= (const Slot &slot);

    /**
     * @brief numSlot identifies the slot in the link.
     */
    int numSlot;
    /**
     * @brief isFree is true, iff the slot is free.
     */
    bool isFree;
    /**
     * @brief firstPos is the first position of this slot along the frequency vector in LinkSpectralDensity.
     */
    unsigned int firstPos;
    /**
     * @brief lastPos is the last position of this slot along the frequency vector in LinkSpectralDensity.
     */
    unsigned int lastPos;
    /**
     * @brief frequencyValues is a vector of the frequency values that this slot represents.
     */
    std::vector<double> frequencyValues;
    /**
     * @brief freeSlot frees this slot, if it isn't free.
     */
    void freeSlot();
    /**
     * @brief useSlot uses this slot, if it isn't used.
     */
    void useSlot();
    /**
     * @brief numFrequencySamplesPerSlot is the number of frequency samples per slot.
     */
    static constexpr unsigned long numFrequencySamplesPerSlot = 25;

    std::shared_ptr<SpectralDensity> S;

    std::shared_ptr<SpectralDensity> X;
};

#endif // SLOT_H
