#include <Devices/Amplifiers/BoosterAmplifier.h>
#include <Devices/SSS.h>

BoosterAmplifier::BoosterAmplifier() : EDFA(-SSS::SSSLoss) {

}

Gain BoosterAmplifier::get_Gain() {
    return AmplifierGain;
}

