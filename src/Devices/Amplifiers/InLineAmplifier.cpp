#include <Devices/Amplifiers/InLineAmplifier.h>
#include <Devices/Fiber.h>

InLineAmplifier::InLineAmplifier(Fiber &Segment) : EDFA(-Segment.get_Gain()) {
    //Each LineAmplifier compensates the losses of the previous fiber segment.
}

Gain InLineAmplifier::get_Gain() {
    return AmplifierGain;
}

std::shared_ptr<Device> InLineAmplifier::clone() {
    return std::shared_ptr<Device>(new InLineAmplifier(*this));
}
