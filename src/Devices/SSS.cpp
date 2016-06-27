#include <Devices/SSS.h>
#include <Structure/Node.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/SpectralDensity.h>
#include <GeneralClasses/LinkSpectralDensity.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralClasses/Signal.h>
#include <GeneralClasses/Transmittances/ConstantTransmittance.h>
#include <GeneralClasses/Transmittances/GaussianPassbandFilter.h>
#include <GeneralClasses/Transmittances/GaussianStopbandFilter.h>

using namespace Devices;
using namespace TF;

Gain SSS::SSSLoss(-5);

SSS::SSS(Node *parent) :
    Device(Device::SSSDevice),
    NoisePower(0, Power::Watt), parent(parent)
{
    filterOrder = SpectralDensity::GaussianOrder;
    deviceTF = std::make_shared<ConstantTransmittance>(get_Gain());
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

std::shared_ptr<Transmittance> SSS::get_TransferFunction(double centerFreq)
{
    if (considerFilterImperfection)
        {
        if (!bypassFunctionsCache.count(centerFreq))
            {
            bypassFunctionsCache[centerFreq] = std::make_shared<GaussianPassbandFilter>
                                               (centerFreq, filterOrder, get_Gain());
            }
        return bypassFunctionsCache.at(centerFreq);
        }
    else
        {
        return deviceTF;
        }
}

std::shared_ptr<Transmittance> SSS::get_BlockTransferFunction(double centerFreq)
{
    if (considerFilterImperfection)
        {
        if (!blockingFunctionsCache.count(centerFreq))
            {
            blockingFunctionsCache[centerFreq] = std::make_shared<GaussianStopbandFilter>
                                                 (centerFreq, filterOrder, get_Gain());
            }
        return blockingFunctionsCache.at(centerFreq);
        }
    else
        {
        return deviceTF;
        }
}
