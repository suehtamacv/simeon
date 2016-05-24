#ifndef LINKSPECTRALDENSITY_H
#define LINKSPECTRALDENSITY_H

#include <GeneralClasses/SpectralDensity.h>
#include <GeneralClasses/Power.h>
#include <Structure/Slot.h>
#include <vector>
#include <memory>
#include <map>

class LinkSpectralDensity
{
public:
    LinkSpectralDensity(std::vector<std::shared_ptr<Slot>>);
    std::vector<std::shared_ptr<Slot>> LinkSlots;
    void updateLink(SpectralDensity, std::vector<std::weak_ptr<Slot>>);
    std::vector<std::shared_ptr<SpectralDensity>> S;
    static unsigned long numFrequencySamples;
    std::shared_ptr<SpectralDensity> slice(unsigned initialSlot,
                                           unsigned finalSlot);
};

#endif // LINKSPECTRALDENSITY_H