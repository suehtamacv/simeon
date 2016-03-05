#include "GeneralClasses/TransferFunctions/TransferFunction.h"

TransferFunction::TransferFunction(double freqMin, double freqMax,
                                   unsigned long int numSamples, double scale) :
    frequencySamples(arma::linspace(freqMin, freqMax, numSamples).t()),
    freqMin(freqMin), freqMax(freqMax), numSamples(numSamples), scale(scale)
{
    isImpulseTransferFunction = false;
}

TransferFunction::TransferFunction(double scale) : scale(scale)
{
    isImpulseTransferFunction = true;
}
