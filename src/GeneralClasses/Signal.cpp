#include <GeneralClasses/Signal.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h>

Power Signal::InputPower = Power(0, Power::dBm);
Gain Signal::InputOSNR = Gain(30, Gain::dB);
unsigned long Signal::numFrequencySamples = 1000; // Mudar de volta para 25

Signal::Signal(unsigned int numSlots) : numSlots(4),
    SignalPower(InputPower),
    NoisePower(InputPower * -InputOSNR) // Fixei numSlots em 4
{
    if(considerFilterImperfection)
        {
        frequencyRange = 4 * Slot::BSlot / 2; // Remover o 4 e colocar numSlots
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
    //Teste
    numSlots = 4;
    frequencyRange = numSlots * Slot::BSlot / 2;
    //Teste

    return Power(
               TrapezoidalRule(signalSpecDensity->specDensity, frequencyRange * 2).calculate()
               * signalSpecDensity->densityScaling, Power::Watt); // Adicionei *2 na freqRange
}

double Signal::get_SignalPowerRatio(int numLinks)
{
    //Teste
    numSlots = 4;
    frequencyRange = numSlots * Slot::BSlot / 2;
    //Teste

    if(originalSpecDensityCache.count(numSlots) == 0)
        {
        SpectralDensity originSD(PhysicalConstants::freq - frequencyRange,
                                 PhysicalConstants::freq + frequencyRange, numFrequencySamples);

        originalSpecDensityCache.emplace(numSlots,
                                         Power(TrapezoidalRule(originSD.specDensity, frequencyRange * 2).calculate()
                                               * originSD.densityScaling, Power::Watt)); // Adicionei *2 na freqRange
        }

    //Teste
    double Result =  get_SpectralPower() / originalSpecDensityCache.at(numSlots);
    if(numLinks == 3)
        std::cout << std::endl << " LINKS = " << numLinks << " SLOTS = " << numSlots << " PR = " << Result << std::endl;
    //Teste

    return Result;
}

double Signal::get_PowerRatioThreshold()
{
    return 0.6;
}
