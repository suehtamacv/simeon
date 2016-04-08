#include <Devices/Amplifiers/Amplifier.h>

using namespace Devices;
using namespace TF;

Amplifier::Amplifier(Gain G) : Device(Device::AmplifierDevice),
    AmplifierGain(G), NoisePower(0)
{

}

Power &Amplifier::get_Noise()
{
    return NoisePower;
}

void Amplifier::set_Gain(Gain G)
{
    AmplifierGain = G;
    deviceTF = std::make_shared<TransferFunction>(std::pow(G.in_Linear(), 2));
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

TransferFunction &Amplifier::get_TransferFunction(unsigned int)
{
    return *deviceTF.get();
}
