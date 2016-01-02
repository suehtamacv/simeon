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

double Amplifier::get_CapEx() {
    return 0;
}

double Amplifier::get_OpEx() {
    return 0.1;
}
