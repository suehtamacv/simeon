#include <Devices/Regenerator.h>
#include <GeneralClasses/Transmittances/ConstantTransmittance.h>

using namespace Devices;
using namespace TF;

Regenerator::Regenerator() : Device(Device::RegeneratorDevice),
    RegeneratorGain(Gain(0)), RegeneratorNoise(Power(0, Power::Watt))
{
    deviceTF = std::make_shared<ConstantTransmittance>(get_Gain());
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

std::shared_ptr<Transmittance> Regenerator::get_TransferFunction(double)
{
    return deviceTF;
}
