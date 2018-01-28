#include <Devices/Amplifiers/BoosterAmplifier.h>
#include <Devices/SSS.h>

using namespace Devices;

BoosterAmplifier::BoosterAmplifier() : EDFA(-SSS::SSSLoss)
{

}

Gain &BoosterAmplifier::get_Gain()
{
    return AmplifierGain;
}

std::shared_ptr<Device> BoosterAmplifier::clone()
{
    return std::shared_ptr<Device>(new BoosterAmplifier(*this));
}
