#include <Devices/Splitter.h>
#include <Structure/Node.h>
#include <GeneralClasses/Transmittances/ConstantTransmittance.h>

using namespace Devices;
using namespace TF;

Splitter::Splitter(Node *parent) : Device(Device::SplitterDevice),
    parent(parent),
    NumPorts(parent->Neighbours.size()),
    SplitterLoss(1.0 / (NumPorts + 1), Gain::Linear),
    NoisePower(0, Power::Watt)
{
    deviceTF = std::make_shared<ConstantTransmittance>(get_Gain());
}

Gain &Splitter::get_Gain()
{
    if (NumPorts != parent->Neighbours.size())
        {
        set_NumPorts(parent->Neighbours.size());
        }
    return SplitterLoss;
}

Power &Splitter::get_Noise()
{
    return NoisePower;
}

void Splitter::set_NumPorts(int NumPorts)
{
    this->NumPorts = NumPorts;
    SplitterLoss = Gain(1.0 / (NumPorts + 1), Gain::Linear);
    deviceTF = std::make_shared<ConstantTransmittance>(get_Gain());
}

std::shared_ptr<Devices::Device> Splitter::clone()
{
    return std::shared_ptr<Devices::Device>(new Splitter(parent));
}

double Splitter::get_CapEx()
{
    return 0.05;
}

double Splitter::get_OpEx()
{
    return 0.2;
}

std::shared_ptr<TF::Transmittance> Splitter::get_TransferFunction(double)
{
    return deviceTF;
}
