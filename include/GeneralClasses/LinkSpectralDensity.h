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

    LinkSpectralDensity &operator *=(TF::TransferFunction &); // TO DO

    Power get_SpectralPower(); // TO DO
    void setSlot(int);
    void clearSlot(int);

    std::shared_ptr<SpectralDensity> S;
    std::shared_ptr<SpectralDensity> X;

    std::vector<double> frequencyValues;
    std::map<unsigned int, std::pair<unsigned int, unsigned int>> slotsPositionsMap;

    static constexpr unsigned long numFrequencySamplesPerSlot = 25;
    static unsigned long numFrequencySamples;
};

#endif // LINKSPECTRALDENSITY_H
