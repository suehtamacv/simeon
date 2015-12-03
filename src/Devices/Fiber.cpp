#include <Devices/Fiber.h>

long double Fiber::alphaFiber = 0.22;

Fiber::Fiber(long double SpanLength) :
    NetLoss(SpanLength * alphaFiber, Gain::init_dB) {
    this->SpanLength = SpanLength;
}

Gain Fiber::get_Gain() {
	return Gain(0);
}

Gain Fiber::get_Loss() {
    return NetLoss;
}

Power Fiber::get_Noise() {
	return Power(0, Power::init_Watt);
}
