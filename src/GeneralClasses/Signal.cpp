#include <GeneralClasses/Signal.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h>

Power Signal::InputPower = Power(0, Power::dBm);
Gain Signal::InputOSNR = Gain(30, Gain::dB);
unsigned long Signal::numFrequencySamples = 1000;

Signal::Signal(unsigned int numSlots) : numSlots(numSlots),
    SignalPower(InputPower),
    NoisePower(InputPower * -InputOSNR)
{
    if(considerFilterImperfection)
        {
        frequencyRange = numSlots * Slot::BSlot / 2;
        signalSpecDensity = std::make_shared<SpectralDensity>(PhysicalConstants::freq -
                            frequencyRange, PhysicalConstants::freq + frequencyRange, numFrequencySamples);
        }
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

Signal &Signal::operator *=(TransferFunction &TF)
{
    if (considerFilterImperfection)
        {
        signalSpecDensity->operator *=(TF);
        }
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

Power Signal::get_SpectralPower()
{
    return Power(
               TrapezoidalRule(signalSpecDensity->specDensity, frequencyRange).calculate()
               * signalSpecDensity->densityScaling, Power::Watt);
}

double Signal::get_SignalPowerRatio()
{
    if(originalSpecDensityCache.count(numSlots) == 0)
        {
        SpectralDensity originSD(PhysicalConstants::freq - frequencyRange / 2,
                                 PhysicalConstants::freq + frequencyRange / 2, numFrequencySamples);
        originalSpecDensityCache.emplace(numSlots, TrapezoidalRule(originSD.specDensity,
                                         frequencyRange).calculate() * originSD.densityScaling);
        }
    return get_SpectralPower() / originalSpecDensityCache.at(numSlots);
}

double Signal::get_PowerRatioThreshold()
{
    return 0.6;
}
