#include <Devices/Fiber.h>

long double Fiber::alphaFiber = 0.22;

Fiber::Fiber(long double SpanLength) :
    NetLoss(SpanLength * alphaFiber, dB::init_dB) {
    this->SpanLength = SpanLength;
}

dB Fiber::get_Gain() {
	return dB(0);
}

dB Fiber::get_Loss() {
    return NetLoss;
}

dB Fiber::get_Noise() {
	return dB(0, dB::init_Linear);
}
