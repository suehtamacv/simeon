#include <Devices/Amplifiers/BoosterAmplifier.h>
#include <Devices/SSS.h>

BoosterAmplifier::BoosterAmplifier() : EDFA(-SSS::SSSLoss)
{
    deviceTF = std::make_shared<TransferFunction>(std::pow(get_Gain().in_Linear(), 2));
}

Gain &BoosterAmplifier::get_Gain()
{
    return AmplifierGain;
}

std::shared_ptr<Device> BoosterAmplifier::clone()
{
    return std::shared_ptr<Device>(new BoosterAmplifier(*this));
}

TransferFunction& BoosterAmplifier::get_TransferFunction(unsigned int)
{
    return *deviceTF.get();
}
