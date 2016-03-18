#include <Devices/SSS.h>
#include <Structure/Node.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralClasses/Signal.h>
#include <GeneralClasses/TransferFunctions/GaussianTransferFunction.h>

Gain SSS::SSSLoss(-5);

SSS::SSS(Node *parent, unsigned int filterOrder) :
    Device(Device::SSSDevice), filterOrder(filterOrder),
    NoisePower(0, Power::Watt), parent(parent)
{

}

Gain &SSS::get_Gain()
{    
    return SSSLoss;
}

Power &SSS::get_Noise()
{
    return NoisePower;
}

std::shared_ptr<Device> SSS::clone()
{
    return std::shared_ptr<Device>(new SSS(*this));
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
    if(transFunctionsCache.count(numSlots) == 0)
        {
        double freqVar = numSlots * Slot::BSlot / 2;
        transFunctionsCache.emplace(numSlots,
                                    GaussianTransferFunction(
                                        PhysicalConstants::freq - freqVar,
                                        PhysicalConstants::freq + freqVar,
                                        Signal::numFrequencySamples,
                                        filterOrder,
                                        std::pow(get_Gain().in_Linear(), 2)));
        }

    return transFunctionsCache.at(numSlots);
}
