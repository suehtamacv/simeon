#include <Devices/Amplifiers/BoosterAmplifier.h>
#include <Devices/SSS.h>

BoosterAmplifier::BoosterAmplifier() : Amplifier(-SSS::SSSLoss) {

}

Gain BoosterAmplifier::get_Gain() {
	return AmplifierGain;
}

