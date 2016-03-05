#include <GeneralClasses/Signal.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>

Power Signal::InputPower = Power(0, Power::dBm);
Gain Signal::InputOSNR = Gain(30, Gain::dB);
unsigned long Signal::numSamples = 1000;

Signal::Signal(unsigned int numSlots) : SignalPower(InputPower),
    NoisePower(InputPower * -InputOSNR)
{
    double freqVar = numSlots * Slot::BSlot / 2;

    signalSpecDensity = std::make_shared<SpectralDensity>(PhysicalConstants::freq - freqVar,
                                                          PhysicalConstants::freq + freqVar, numSamples);
}

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
