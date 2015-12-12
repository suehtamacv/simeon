#include <Devices/Amplifiers/Amplifier.h>

Amplifier::Amplifier(Gain G) : Device(Device::AmplifierDevice),
    AmplifierGain(G), NoisePower(0) {

}

Power &Amplifier::get_Noise() {
    return NoisePower;
}

void Amplifier::set_Gain(Gain G) {
    AmplifierGain = G;
    calculate_NoisePower();
}
