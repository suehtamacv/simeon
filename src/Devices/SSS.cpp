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

TransferFunction& SSS::get_TransferFunction(double centerFreq,
        double bandwidth)
{
    if (considerFilterImperfection)
        {
        auto freq = std::make_pair(centerFreq, bandwidth);
        int numSlots = std::round(bandwidth / Slot::BSlot);

        if (!bypassFunctionsCache.count(freq))
            {
            bypassFunctionsCache[freq] = GaussianTransferFunction(
                                             centerFreq - bandwidth / 2.0,
                                             centerFreq + bandwidth / 2.0,
                                             Slot::numFrequencySamplesPerSlot * numSlots,
                                             filterOrder, std::pow(get_Gain().in_Linear(), 2));
            }
        return bypassFunctionsCache.at(freq);
        }
    else
        {
        return *deviceTF;
        }
}

TransferFunction& SSS::get_BlockTransferFunction(double centerFreq,
        double bandwidth)
{
    if (considerFilterImperfection)
        {
        auto freq = std::make_pair(centerFreq, bandwidth);
        int numSlots = std::round(bandwidth / Slot::BSlot);

        if (!blockingFunctionsCache.count(freq))
            {
            blockingFunctionsCache[freq] = GaussianTransferFunction(
                                               centerFreq - bandwidth / 2.0,
                                               centerFreq + bandwidth / 2.0,
                                               Slot::numFrequencySamplesPerSlot * numSlots,
                                               filterOrder, std::pow(get_Gain().in_Linear(), 2));
            //Stopband filter
            blockingFunctionsCache[freq].frequencySamples
                = 1.0 - blockingFunctionsCache[freq].frequencySamples;
            }
        return blockingFunctionsCache.at(freq);
        }
    else
        {
        return *deviceTF;
        }
}
