#include <Devices/Fiber.h>

double Fiber::alphaFiber = 0.22;

Fiber::Fiber(double SpanLength) :
    Device(Device::FiberDevice), NetLoss(- SpanLength * alphaFiber, Gain::dB),
    NoisePower(0, Power::Watt) {
    this->SpanLength = SpanLength;
}

Gain &Fiber::get_Gain() {
    return NetLoss;
}

Power &Fiber::get_Noise() {
    return NoisePower;
}

std::shared_ptr<Device> Fiber::clone() {
    return std::shared_ptr<Device>(new Fiber(*this));
}

double Fiber::get_CapEx() {
    return 0;
}

double Fiber::get_OpEx() {
    return 0;
}
