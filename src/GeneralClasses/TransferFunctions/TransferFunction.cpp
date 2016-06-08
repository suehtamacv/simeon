#include "GeneralClasses/TransferFunctions/TransferFunction.h"

using namespace TF;

TransferFunction::TransferFunction
(double freqMin, double freqMax, unsigned long int numSamples, double scale) :
    frequencySamples(arma::linspace(freqMin, freqMax, numSamples).t()),
    scale(scale), freqMin(freqMin), freqMax(freqMax)
{
    isImpulseTransferFunction = false;
}

TransferFunction::TransferFunction(double scale) : scale(scale)
{
    freqMin = freqMax = 0;
    isImpulseTransferFunction = true;
}

bool TransferFunction::operator ==(const TransferFunction &tf) const
{
    if ((freqMin != tf.freqMin) ||
            (freqMax != tf.freqMax) ||
            (isImpulseTransferFunction != tf.isImpulseTransferFunction) ||
            (frequencySamples.n_cols != tf.frequencySamples.n_cols))
        {
        return false;
        }

    if (isImpulseTransferFunction)
        {
        return (scale == tf.scale);
        }
    else
        {
        bool isEqual = true;
        for (size_t c = 0; isEqual && (c < frequencySamples.n_cols); ++c)
            {
            isEqual &= (scale * frequencySamples[c]) == (tf.scale * tf.frequencySamples[c]);
            }
        return isEqual;
        }
}
