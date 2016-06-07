#include <Devices/Fiber.h>

using namespace Devices;
using namespace TF;

double Fiber::alphaFiber = 0.22;

Fiber::Fiber(double SpanLength) :
    Device(Device::FiberDevice), NetLoss(- SpanLength * alphaFiber, Gain::dB),
    NoisePower(0, Power::Watt)
{
    this->SpanLength = SpanLength;

    deviceTF = std::make_shared<TransferFunction>(std::pow(get_Gain().in_Linear(), 2));
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

TransferFunction& Fiber::get_TransferFunction(double, double)
{
    return *deviceTF.get();
}
