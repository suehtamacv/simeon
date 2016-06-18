#include <Devices/Fiber.h>
#include <GeneralClasses/TransferFunctions/ConstantTransmittance.h>

using namespace Devices;
using namespace TF;

double Fiber::alphaFiber = 0.22;

Fiber::Fiber(double SpanLength) :
    Device(Device::FiberDevice), NetLoss(- SpanLength * alphaFiber, Gain::dB),
    NoisePower(0, Power::Watt)
{
    this->SpanLength = SpanLength;
    deviceTF = std::make_shared<ConstantTransmittance>(get_Gain());
}

Gain &Fiber::get_Gain()
{
    return NetLoss;
}

Power &Fiber::get_Noise()
{
    return NoisePower;
}

std::shared_ptr<Device> Fiber::clone()
{
    return std::shared_ptr<Device>(new Fiber(*this));
}

double Fiber::get_CapEx()
{
    return 0;
}

double Fiber::get_OpEx()
{
    return 0;
}

std::shared_ptr<Transmittance> Fiber::get_TransferFunction(double)
{
    return deviceTF;
}
