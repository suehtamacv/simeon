#include <GeneralClasses/Signal.h>

Power Signal::InputPower = Power(0, Power::dBm);
Gain Signal::InputOSNR = Gain(30, Gain::dB);
unsigned long Signal::numSamples = 1000;

Signal::Signal() : SignalPower(InputPower),
    NoisePower(InputPower * -InputOSNR) { }

Signal &Signal::operator *=(Gain &G)
{
    SignalPower *= G;
    NoisePower *= G;
    return *this;
}

Signal &Signal::operator +=(Power &P)
{
    NoisePower += P;
    return *this;
}

Gain Signal::get_OSNR()
{
    return Gain(SignalPower.in_dBm() - NoisePower.in_dBm());
}

Power Signal::get_NoisePower()
{
    return Power(NoisePower);
}
