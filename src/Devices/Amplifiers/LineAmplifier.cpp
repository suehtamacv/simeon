#include <Devices/Amplifiers/LineAmplifier.h>
#include <Devices/Fiber.h>

LineAmplifier::LineAmplifier(Fiber &Segment) : EDFA(-Segment.get_Loss()) {
    //Each LineAmplifier compensates the losses of the previous fiber segment.
}

Gain LineAmplifier::get_Gain() {
    return AmplifierGain;
}

