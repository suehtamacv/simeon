#ifndef GAUSSIANFILTER_H
#define GAUSSIANFILTER_H

#include <GeneralClasses/Transmittances/Transmittance.h>
#include <map>

namespace TF
{
/**
 * @brief The GaussianFilter class represents the transmittance of a Gaussian filter.
 */
class GaussianFilter : public Transmittance
{
public:
    /**
     * @brief GaussianFilter is a constructor for a GaussianFilter.
     * @param centerFreq is the central frequency of this filter.
     * @param filterOrder is the order of the gaussian filter.
     * @param scale is the scale of this filter.
     */
    GaussianFilter(double centerFreq, unsigned int filterOrder, Gain scale);
    /**
     * @brief BW_3dB is the bandwidth of optical filter at 3dB.
     */
    static constexpr double BW_3dB = 41e9;

    double &get_CenterFreq();
    unsigned int &get_FilterOrder();

protected:
    double centerFreq;
    unsigned int filterOrder;
    std::map<double, Gain> calculatedGains;
};
}

#endif // GAUSSIANFILTER_H
