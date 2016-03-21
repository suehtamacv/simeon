#include "GeneralClasses/SpectralDensity.h"
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralClasses/Signal.h>
#include <Structure/Slot.h>

std::map<std::pair<double, double>, arma::rowvec>
SpectralDensity::specDensityMap;

int SpectralDensity::GaussianOrder = 1;

SpectralDensity::SpectralDensity
(double freqMin, double freqMax, unsigned int numSamples) : densityScaling(1),
    freqMin(freqMin), freqMax(freqMax)
{
    std::pair<double, double> freqValues = std::make_pair(freqMin, freqMax);

    if(specDensityMap.count(freqValues) == 0)
        {
        arma::rowvec thisSpecDensity = arma::linspace(freqMin, freqMax, numSamples).t();
        std::cout << thisSpecDensity << std::endl;
        for (auto& val : thisSpecDensity)
            {
            val = std::exp2l( (-2) * pow( 2 * (val - PhysicalConstants::freq) / SBW_3dB,
                                          2 * GaussianOrder));
            }
        std::cout << thisSpecDensity << std::endl;
        specDensityMap.emplace(freqValues, thisSpecDensity);
        }
    specDensity = specDensityMap[freqValues];
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
    std::cout << std::endl << "-> Enter the SSS optical filter order." << std::endl;

    do
        {

        int filterOrder;
        std::cin >> filterOrder;

        if (std::cin.fail() || filterOrder < 1)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Filter Order." << std::endl;
            std::cout << std::endl << "-> Enter the SSS optical filter order." << std::endl;
            }
        else
            {
            GaussianOrder = filterOrder;
            break;
            }
        }
    while (1);
}
