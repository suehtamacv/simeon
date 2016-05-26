#include <GeneralClasses/Signal.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h>
#include <GeneralClasses/LinkSpectralDensity.h>

using namespace TF;
using namespace NumericMethods;

Power Signal::InputPower = Power(0, Power::dBm);
Gain Signal::InputOSNR = Gain(30, Gain::dB);

Signal::Signal(unsigned int numSlots) : numSlots(numSlots),
    SignalPower(InputPower),
    NoisePower(InputPower * -InputOSNR)
{
    if(considerFilterImperfection)
        {
        frequencyRange = numSlots * Slot::BSlot / 2;
        signalSpecDensity = std::make_shared<SpectralDensity>(PhysicalConstants::freq -
                            frequencyRange, PhysicalConstants::freq + frequencyRange,
                            (int) Slot::numFrequencySamplesPerSlot * numSlots);
        X = std::make_shared<SpectralDensity>(PhysicalConstants::freq - frequencyRange,
                                              PhysicalConstants::freq + frequencyRange,
                                              (int) Slot::numFrequencySamplesPerSlot * numSlots, true);
        }
}

Signal::Signal(std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
               std::owner_less<std::weak_ptr<Link>>>  occupiedSlots) : occupiedSlots(
                       occupiedSlots),
    SignalPower(InputPower),
    NoisePower(InputPower * -InputOSNR)
{
    numSlots = occupiedSlots.begin()->second.size();
    if(considerFilterImperfection)
        {
        frequencyRange = numSlots * Slot::BSlot / 2;
        signalSpecDensity = std::make_shared<SpectralDensity>(PhysicalConstants::freq -
                            frequencyRange, PhysicalConstants::freq + frequencyRange,
                            (int) Slot::numFrequencySamplesPerSlot * numSlots);
        X = std::make_shared<SpectralDensity>(PhysicalConstants::freq - frequencyRange,
                                              PhysicalConstants::freq + frequencyRange,
                                              (int) Slot::numFrequencySamplesPerSlot * numSlots, true);
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
        (*signalSpecDensity) *= (TF);
        }
    return *this;
}

Signal &Signal::operator +=(SpectralDensity &PSD)
{
    (*X) += (PSD);
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
               TrapezoidalRule(signalSpecDensity->specDensity, frequencyRange * 2).calculate()
               * signalSpecDensity->densityScaling, Power::Watt);
}

double Signal::get_SignalPowerRatio()
{
    if (!originalSpecDensityCache.count(numSlots))
        {
        SpectralDensity originSD(PhysicalConstants::freq - frequencyRange,
                                 PhysicalConstants::freq + frequencyRange,
                                 Slot::numFrequencySamplesPerSlot * numSlots);

        originalSpecDensityCache.emplace(numSlots, Power(
                                             TrapezoidalRule(originSD.specDensity, frequencyRange * 2).calculate()
                                             * originSD.densityScaling, Power::Watt));
        }
    return get_SpectralPower() / originalSpecDensityCache.at(numSlots);
}
