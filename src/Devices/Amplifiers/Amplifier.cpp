#include <Devices/Amplifiers/Amplifier.h>
#include <GeneralClasses/PhysicalConstants.h>

Gain Amplifier::NoiseFigure = Gain(5);
long double Amplifier::BRef = 12.5E9;

Amplifier::Amplifier(Gain G) : AmplifierGain(G), NoisePower(0) {
    calculate_NoisePower();
}

Gain Amplifier::get_Loss() {
    return Gain(0);
}

Power Amplifier::get_Noise() {
    return NoisePower;
}

void Amplifier::calculate_NoisePower() {
    //This is the ASE Noise Modelling.
    long double Noise = 0.5 * PhysicalConstants::h * PhysicalConstants::freq *
                        Amplifier::BRef * NoiseFigure.in_Linear() * (AmplifierGain.in_Linear() - 1);
    NoisePower = Power(Noise, Power::Watt);
}

void Amplifier::set_Gain(Gain G) {
    AmplifierGain = G;
    calculate_NoisePower();
}
