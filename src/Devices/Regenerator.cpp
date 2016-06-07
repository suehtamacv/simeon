#include <Devices/Regenerator.h>

using namespace Devices;
using namespace TF;

Regenerator::Regenerator() : Device(Device::RegeneratorDevice),
    RegeneratorGain(Gain(0)), RegeneratorNoise(Power(0, Power::Watt))
{
    deviceTF = std::make_shared<TransferFunction>(std::pow(get_Gain().in_Linear(), 2));
}

Gain &Regenerator::get_Gain()
{
    return RegeneratorGain;
}

Power &Regenerator::get_Noise()
{
    return RegeneratorNoise;
}

double Regenerator::get_CapEx()
{
    return 1.0;
}

double Regenerator::get_OpEx()
{
    return 0.2;
}

std::shared_ptr<Device> Regenerator::clone()
{
    return std::shared_ptr<Device>(new Regenerator());
}

TransferFunction& Regenerator::get_TransferFunction(double, double)
{
    return *deviceTF.get();
}
