#include <Devices/Splitter.h>
#include <Structure/Node.h>

Splitter::Splitter(Node *parent) : Device(Device::SplitterDevice),
    parent(parent),
    NumPorts(parent->Neighbours.size()),
    SplitterLoss(1.0 / (NumPorts + 1), Gain::Linear),
    NoisePower(0, Power::Watt)
{
    deviceTF = std::make_shared<TransferFunction>(std::pow(get_Gain().in_Linear(),
               2));
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
    deviceTF = std::make_shared<TransferFunction>
               (std::pow(get_Gain().in_Linear(), 2));
}

std::shared_ptr<Device> Splitter::clone()
{
    return std::shared_ptr<Device>(new Splitter(parent));
}

double Splitter::get_CapEx()
{
    return 0.05;
}

double Splitter::get_OpEx()
{
    return 0.2;
}

TransferFunction& Splitter::get_TransferFunction(unsigned int)
{
    return *deviceTF.get();
}
