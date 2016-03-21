#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <armadillo>
#include <vector>

/**
 * @brief The TransferFunction class represents the absolute value squared of a transfer function.
 */
class TransferFunction
{
public:
    TransferFunction(double freqMin, double freqMax,
                     unsigned long int numSamples, double scale);
    TransferFunction(double scale);

    //Vector contendo os valores da função de transferência a serem multiplicados com a densidade espectral do sinal.
    arma::rowvec frequencySamples;
    double scale;
    bool isImpulseTransferFunction;

    double freqMin;
    double freqMax;
    unsigned long int numSamples;
};

#endif // TRANSFERFUNCTION_H
