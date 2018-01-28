#ifndef GAUSSIANSTOPBANDFILTER_H
#define GAUSSIANSTOPBANDFILTER_H

#include "GaussianFilter.h"

namespace TF
{
/**
 * @brief The GaussianStopbandFilter class represents the transmittance of a
 * stopband Gaussian filter.
 */
class GaussianStopbandFilter : public GaussianFilter
{
public:
    /**
     * @brief GaussianStopbandFilter is a constructor for a GaussianStopbandFilter.
     * @param centerFreq is the central frequency of this filter.
     * @param filterOrder is the order of the gaussian filter.
     * @param scale is the scale of this filter.
     */
    GaussianStopbandFilter(double centerFreq, unsigned int filterOrder, Gain scale);
    Gain& get_TransmittanceAt(double freq);
};
}

#endif // GAUSSIANSTOPBANDFILTER_H
