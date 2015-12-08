#include <GeneralClasses/Signal.h>

Power Signal::InputPower = Power(0, Power::dBm);
Gain Signal::InputOSNR = Gain(30, Gain::dB);

Signal::Signal() : SignalPower(InputPower) ,
	NoisePower(InputPower * -InputOSNR) { }

void Signal::operator *=(Gain G) {
	SignalPower *= G;
	NoisePower *= G;
}

void Signal::operator +=(Power P) {
	NoisePower += P;
}

Gain Signal::get_OSNR() {
    return Gain(SignalPower.in_dBm() - NoisePower.in_dBm());
}

