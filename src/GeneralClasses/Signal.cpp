#include <GeneralClasses/Signal.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h>
#include <GeneralClasses/LinkSpectralDensity.h>

using namespace TF;
using namespace NumericMethods;

Power Signal::InputPower = Power(0, Power::dBm);
Gain Signal::InputOSNR = Gain(30, Gain::dB);

Signal::Signal(mapSlots occupiedSlots) : occupiedSlots(occupiedSlots),
    SignalPower(InputPower),
    NoisePower(InputPower * -InputOSNR)
{
    std::sort(occupiedSlots.begin()->second.begin(),
              occupiedSlots.begin()->second.end(),
              [](const std::weak_ptr<Slot> &l, const std::weak_ptr<Slot> &r)
        {
        return l.lock()->numSlot < r.lock()->numSlot;
        });

    numSlots = occupiedSlots.begin()->second.size();
    freqMin = occupiedSlots.begin()->second.front().lock()->S->freqMin;
    freqMax = occupiedSlots.begin()->second.back().lock()->S->freqMax;
    if(considerFilterImperfection)
        {
        signalSpecDensity = std::make_shared<SpectralDensity>(freqMin, freqMax,
                            (int) Slot::samplesPerSlot * numSlots);
        crosstalkSpecDensity = std::make_shared<SpectralDensity>(freqMin, freqMax,
                               (int) Slot::samplesPerSlot * numSlots, true);
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

Signal &Signal::operator *=(std::shared_ptr<Transmittance> TF)
{
    if (considerFilterImperfection)
        {
        (*signalSpecDensity) *= TF;
        (*crosstalkSpecDensity) *= TF;
        }
    return *this;
}

Signal &Signal::operator +=(SpectralDensity &PSD)
{
    if (considerFilterImperfection)
        {
        (*crosstalkSpecDensity) += (PSD);
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
               TrapezoidalRule().calculate(signalSpecDensity->specDensity, freqMax - freqMin)
               * signalSpecDensity->densityScaling.in_Linear(), Power::Watt);
}

Gain Signal::get_SignalPowerRatio()
{
    if (!originalSpecDensityCache.count(numSlots))
        {
        SpectralDensity originSD(freqMin, freqMax,
                                 Slot::samplesPerSlot * numSlots);

        originalSpecDensityCache.emplace(numSlots, Power(
                                             TrapezoidalRule().calculate(originSD.specDensity, freqMax - freqMin)
                                             * originSD.densityScaling.in_Linear(), Power::Watt));
        }
    return get_SpectralPower() / originalSpecDensityCache.at(numSlots);
}

Gain Signal::get_WeightedCrosstalk()
{
    arma::rowvec S = signalSpecDensity->specDensity * signalSpecDensity->densityScaling.in_Linear();
    arma::rowvec X = crosstalkSpecDensity->specDensity * crosstalkSpecDensity->densityScaling.in_Linear();

    double P = TrapezoidalRule().calculate(S, freqMax - freqMin);
    double k = P / TrapezoidalRule().calculate(S % S, freqMax - freqMin);

    return
        Gain(TrapezoidalRule().calculate(k * S % X, freqMax - freqMin) / P, Gain::Linear);
}
