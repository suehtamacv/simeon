#include <Devices/Amplifiers/Amplifier.h>
#include <GeneralClasses/TransferFunctions/ConstantTransmittance.h>

using namespace Devices;
using namespace TF;

Amplifier::Amplifier(Gain G) : Device(Device::AmplifierDevice),
    AmplifierGain(G), NoisePower(0)
{
    deviceTF = std::make_shared<ConstantTransmittance>(G);
}

Power &Amplifier::get_Noise()
{
    return NoisePower;
}

void Amplifier::set_Gain(Gain G)
{
    AmplifierGain = G;
    deviceTF = std::make_shared<ConstantTransmittance>(get_Gain());
    calculate_NoisePower();
}

double Amplifier::get_CapEx()
{
    return 0;
}

double Amplifier::get_OpEx()
{
    return 0.1;
}

std::shared_ptr<Transmittance> Amplifier::get_TransferFunction(double)
{
    return deviceTF;
}
