#include <Devices/SSS.h>
#include <Structure/Node.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/SpectralDensity.h>
#include <GeneralClasses/LinkSpectralDensity.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralClasses/Signal.h>
#include <GeneralClasses/TransferFunctions/GaussianTransferFunction.h>

using namespace Devices;
using namespace TF;

Gain SSS::SSSLoss(-5);

SSS::SSS(Node *parent) :
    Device(Device::SSSDevice),
    NoisePower(0, Power::Watt), parent(parent)
{
    filterOrder = SpectralDensity::GaussianOrder;
    deviceTF = std::make_shared<TransferFunction>
               (std::pow(get_Gain().in_Linear(), 2));
}

Gain &SSS::get_Gain()
{
    return SSSLoss;
}

Power &SSS::get_Noise()
{
    return NoisePower;
}

std::shared_ptr<Devices::Device> SSS::clone()
{
    return std::shared_ptr<Devices::Device>(new SSS(*this));
}

double SSS::get_CapEx()
{
    int numPorts = parent->Neighbours.size() + 1;

    if (numPorts <= 4)
        {
        return 2.35;
        }
    else if (numPorts <= 8)
        {
        return 4.70;
        }
    else if (numPorts <= 20)
        {
        return 7.05;
        }
    else if (numPorts <= 40)
        {
        return 10.58;
        }
    else
        {
        return -1;
        }
}

double SSS::get_OpEx()
{
    return 0.2;
}

TransferFunction& SSS::get_TransferFunction(unsigned int numSlots)
{
    if (considerFilterImperfection)
        {
        if(bypassFunctionsCache.count(numSlots) == 0)
            {
            double freqVar = numSlots * Slot::BSlot / 2;
            bypassFunctionsCache.emplace(numSlots,
                                         GaussianTransferFunction(
                                             PhysicalConstants::freq - freqVar,
                                             PhysicalConstants::freq + freqVar,
                                             Slot::numFrequencySamplesPerSlot * numSlots,
                                             filterOrder,
                                             std::pow(get_Gain().in_Linear(), 2)));
            blockingFunctionsCache.emplace(numSlots,
                                           GaussianTransferFunction(
                                               PhysicalConstants::freq - freqVar,
                                               PhysicalConstants::freq + freqVar,
                                               Slot::numFrequencySamplesPerSlot * numSlots,
                                               filterOrder,
                                               std::pow(get_Gain().in_Linear(), 2)));
            blockingFunctionsCache.at(numSlots).frequencySamples =
                1.0 - blockingFunctionsCache.at(numSlots).frequencySamples;
            }
        return bypassFunctionsCache.at(numSlots);
        }
    else
        {
        return *deviceTF;
        }
}

std::shared_ptr<SpectralDensity> SSS::get_InterferingSignal(
    std::weak_ptr<Link> incomingLink,
    unsigned initialSlot,
    unsigned finalSlot)
{
    int numSlots = finalSlot - initialSlot + 1;
    get_TransferFunction(numSlots);
    double frequencyRange = numSlots * Slot::BSlot / 2;
    auto X = std::make_shared<SpectralDensity>(PhysicalConstants::freq -
             frequencyRange, PhysicalConstants::freq + frequencyRange,
             Slot::numFrequencySamplesPerSlot * numSlots, true);

    for (std::shared_ptr<Link> &link : parent->incomingLinks)
        {
        if (incomingLink.lock() != link)
            {
            X->operator+=(*(link->linkSpecDens->slice(initialSlot, finalSlot))
                          * blockingFunctionsCache.at(numSlots));
            }
        }

    return X;
}