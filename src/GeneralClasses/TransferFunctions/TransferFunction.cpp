#include "GeneralClasses/TransferFunctions/TransferFunction.h"

using namespace TF;

TransferFunction::TransferFunction
(double freqMin, double freqMax, unsigned long int numSamples, double scale) :
    frequencySamples(arma::linspace(freqMin, freqMax, numSamples).t()),
    scale(scale), freqMin(freqMin), freqMax(freqMax), numSamples(numSamples)
{
    isImpulseTransferFunction = false;
}

TransferFunction::TransferFunction(double scale) : scale(scale)
{
    isImpulseTransferFunction = true;
}
