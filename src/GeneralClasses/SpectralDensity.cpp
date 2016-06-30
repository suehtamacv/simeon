#include "GeneralClasses/SpectralDensity.h"
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralClasses/Signal.h>
#include <Structure/Slot.h>

using namespace TF;

std::map<std::pair<double, double>, arma::rowvec>
SpectralDensity::specDensityMap;

int SpectralDensity::GaussianOrder = 1;
int SpectralDensity::TxFilterOrder = 1;

SpectralDensity::SpectralDensity
(double freqMin, double freqMax, unsigned int numSamples, bool cleanSpec) :
    densityScaling(0, Gain::dB), freqMin(freqMin), freqMax(freqMax)
{
    stepFrequency = (freqMax - freqMin) / (double) numSamples;

    if (cleanSpec)
        {
        specDensity.zeros(numSamples);
        }
    else
        {
        double centerFreq = (freqMax + freqMin) / 2.0;
        std::pair<double, double> freqValues = {freqMin, freqMax};

        if (!specDensityMap.count(freqValues))
            {
            arma::rowvec thisSpecDensity = arma::linspace(freqMin, freqMax, numSamples).t();
            for (auto& val : thisSpecDensity)
                {
                val = std::exp2l(-pow(2 * (val - centerFreq) / SBW_3dB, 2 * TxFilterOrder));
                }
            specDensityMap[freqValues] = thisSpecDensity;
            }
        specDensity = specDensityMap[freqValues];
        }
}

SpectralDensity::SpectralDensity(const SpectralDensity &spec) :
    densityScaling(spec.densityScaling),
    freqMin(spec.freqMin),
    freqMax(spec.freqMax),
    specDensity(spec.specDensity),
    stepFrequency(spec.stepFrequency)
{

}

bool SpectralDensity::operator ==(const SpectralDensity &originSpecDens) const
{
    size_t i = 0;
    bool specFlag = true;
    for(auto& val : originSpecDens.specDensity)
    {
        if(specDensity(i) != val)
        {
            specFlag = false;
        }
        i++;
    }

    return (densityScaling == originSpecDens.densityScaling && freqMin == originSpecDens.freqMin &&
            freqMax == originSpecDens.freqMax && specFlag &&
            stepFrequency == originSpecDens.stepFrequency);
}

SpectralDensity& SpectralDensity::operator *=(std::shared_ptr<TF::Transmittance> H)
{
    for (size_t c = 0; c < specDensity.n_cols; ++c)
        {
        specDensity[c] *= H->get_TransmittanceAt(freqMin + c * stepFrequency).in_Linear();
        }
    return *this;
}

void SpectralDensity::define_SignalsFilterOrder()
{
    std::cout << std::endl <<
              "-> Enter the transmitted signal optical filter order. "
              << std::endl;

    do
        {
        int filterOrder;
        std::cin >> filterOrder;

        if (std::cin.fail() || filterOrder < 1 || filterOrder > 10)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Filter Order." << std::endl;
            std::cout << std::endl <<
                      "-> Enter the transmitted signal optical filter order."
                      << std::endl;
            }
        else
            {
            TxFilterOrder = filterOrder;
            break;
            }
        }
    while (1);

    std::cout << std::endl
              << "-> Enter the path SSSs optical filter order."
              << std::endl;

    do
        {

        int filterOrder;
        std::cin >> filterOrder;

        if (std::cin.fail() || filterOrder < 1 || filterOrder > 10)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Filter Order." << std::endl;
            std::cout << std::endl
                      << "-> Enter the path SSSs optical filter order."
                      << std::endl;
            }
        else
            {
            GaussianOrder = filterOrder;
            break;
            }
        }
    while (1);
}

SpectralDensity& SpectralDensity::operator +=(const SpectralDensity &PSD)
{
#ifdef RUN_ASSERTIONS
    if ((freqMin != PSD.freqMin) || (freqMax != PSD.freqMax))
        {
        std::cerr << "Error summing two spectral densities." << std::endl;
        abort();
        }
#endif
    specDensity = densityScaling.in_Linear() * specDensity +
                  Gain(PSD.densityScaling).in_Linear() * PSD.specDensity;
    densityScaling = Gain(0, Gain::dB);
    return *this;
}

SpectralDensity SpectralDensity::operator *(std::shared_ptr<TF::Transmittance> H) const
{
    SpectralDensity spec(*this);
    spec *= H;
    return spec;
}
