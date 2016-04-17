#ifndef LINKSPECTRALDENSITY_H
#define LINKSPECTRALDENSITY_H

#include <GeneralClasses/SpectralDensity.h>
#include <GeneralClasses/Power.h>
#include <vector>
#include <memory>
#include <map>

class LinkSpectralDensity
{
public:
    LinkSpectralDensity();

    LinkSpectralDensity &operator *=(TF::TransferFunction &);

    Power get_SpectralPower();
    std::vector<SpectralDensity> get_SlotsSpecDensity(int firstSlot, int FinalSlot);

    std::shared_ptr<SpectralDensity> S();
    std::shared_ptr<SpectralDensity> X();
    std::vector<double> frequencyValues;

    static constexpr unsigned long numFrequencySamplesPerSlot = 25;
    static unsigned long numFrequencySamples;
};

#endif // LINKSPECTRALDENSITY_H
