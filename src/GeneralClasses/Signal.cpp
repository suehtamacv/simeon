#include <GeneralClasses/Signal.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralPurposeAlgorithms/IntegrationMethods/SimpsonsRule.h>
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
                            (int) Slot::numFrequencySamplesPerSlot * numSlots);
        crosstalkSpecDensity = std::make_shared<SpectralDensity>(freqMin, freqMax,
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
    (*crosstalkSpecDensity) += (PSD);
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
               SimpsonsRule().calculate(signalSpecDensity->specDensity, freqMax - freqMin)
               * signalSpecDensity->densityScaling, Power::Watt);
}

double Signal::get_SignalPowerRatio()
{
    if (!originalSpecDensityCache.count(numSlots))
        {
        SpectralDensity originSD(freqMin, freqMax,
                                 Slot::numFrequencySamplesPerSlot * numSlots);

        originalSpecDensityCache.emplace(numSlots, Power(
                                             SimpsonsRule().calculate(originSD.specDensity, freqMax - freqMin)
                                             * originSD.densityScaling, Power::Watt));
        }
    return get_SpectralPower() / originalSpecDensityCache.at(numSlots);
}

Gain Signal::get_WeightedCrosstalk()
{
    arma::rowvec S = signalSpecDensity->specDensity;
    arma::rowvec X = crosstalkSpecDensity->specDensity;

    double P = SimpsonsRule().calculate(S, freqMax - freqMin);
    double k = P / SimpsonsRule().calculate(S % S, freqMax - freqMin);

    return
        Gain(SimpsonsRule().calculate(k * S % X, freqMax - freqMin) / k, Gain::Linear);
}
