#ifndef GAUSSIANPASSBANDFILTER_H
#define GAUSSIANPASSBANDFILTER_H

#include "GaussianFilter.h"

namespace TF
{
/**
 * @brief The GaussianPassbandFilter class represents the transmittance of a
 * passband Gaussian filter.
 */
class GaussianPassbandFilter : public GaussianFilter
{
public:
    /**
     * @brief GaussianPassbandFilter is a constructor for a GaussianPassbandFilter.
     * @param centerFreq is the central frequency of this filter.
     * @param filterOrder is the order of the gaussian filter.
     * @param scale is the scale of this filter.
     */
    GaussianPassbandFilter(double centerFreq, unsigned int filterOrder, Gain scale);
    Gain get_TransmittanceAt(double freq);
};
}

#endif // GAUSSIANPASSBANDFILTER_H
