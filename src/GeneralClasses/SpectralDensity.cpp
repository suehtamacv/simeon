#include "GeneralClasses/SpectralDensity.h"
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralClasses/Signal.h>
#include <boost/assert.hpp>
#include <Structure/Slot.h>

using namespace TF;

std::map<std::pair<double, double>, arma::rowvec>
SpectralDensity::specDensityMap;

int SpectralDensity::GaussianOrder = 1;
int SpectralDensity::TxFilterOrder = 1;

SpectralDensity::SpectralDensity
(double freqMin, double freqMax, unsigned int numSamples, bool cleanSpec) :
    densityScaling(1), freqMin(freqMin), freqMax(freqMax)
{
    if (cleanSpec)
        {
        specDensity.zeros(numSamples);
        }
    else
        {
        double centerFreq = (freqMax + freqMin) / 2.0;
        std::pair<double, double> freqValues = {freqMin, freqMax};

        if (specDensityMap.count(freqValues) == 0)
            {
            arma::rowvec thisSpecDensity = arma::linspace(freqMin, freqMax, numSamples).t();
            for (auto& val : thisSpecDensity)
                {
                val = std::exp2l( (-2) *
                                  pow(2 * (val - centerFreq) / SBW_3dB, 2 * TxFilterOrder));
                }
            specDensityMap.emplace(freqValues, thisSpecDensity);
            }
        specDensity = specDensityMap[freqValues];
        }
}

SpectralDensity::SpectralDensity(const SpectralDensity &spec)
{
    TxFilterOrder = spec.TxFilterOrder;
    GaussianOrder = spec.GaussianOrder;
    densityScaling = spec.densityScaling;
    freqMin = spec.freqMin;
    freqMax = spec.freqMax;
    specDensity = arma::rowvec(spec.specDensity);
    specDensityMap = spec.specDensityMap;
}

SpectralDensity& SpectralDensity::operator *=(TransferFunction &H)
{
    densityScaling *= H.scale;
    if (!H.isImpulseTransferFunction)
        {
        specDensity %= H.frequencySamples;
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
    BOOST_ASSERT_MSG((freqMin == PSD.freqMin) && (freqMax == PSD.freqMax),
                     "Error summing two spectral densities");
    specDensity = densityScaling * specDensity +
                  PSD.densityScaling * PSD.specDensity;
    densityScaling = 1;
    return *this;
}

SpectralDensity SpectralDensity::operator *(TF::TransferFunction &H) const
{
    SpectralDensity spec(*this);
    spec *= H;
    return spec;
}
