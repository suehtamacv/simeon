#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <armadillo>
#include <vector>


//! Contains models for the transfer functions of optical devices.
namespace TF
{
/**
 * @brief The TransferFunction class represents the absolute value squared of a transfer function.
 */
class TransferFunction
{
public:
    /**
     * @brief TransferFunction is a constructor for a TransferFunction.
     * @param freqMin is the beginning of the signal's bandwidth.
     * @param freqMax is the end of the signal's bandwidth.
     * @param numSamples is the number of frequency samples along the bandwidth.
     * @param scale is the result of the gains and losses over this transfer function.
     */
    TransferFunction(double freqMin, double freqMax,
                     unsigned long int numSamples, double scale);
    /**
     * @brief TransferFunction is a constructor for a TransferFunction.
     * @param scale is the result of the gains and losses over this transfer function.
     */
    TransferFunction(double scale = 1);
    /**
     * @brief frequencySamples is a vector with the frequency samples along the signal's bandwidth.
     */
    arma::rowvec frequencySamples;
    /**
     * @brief scale is the result of the gains and losses over this transfer function.
     */
    double scale;
    /**
     * @brief isImpulseTransferFunction is a flag to indicate that this transfer function doesn't
     * apply changes to a signal spectral density.
     */
    bool isImpulseTransferFunction;
    /**
     * @brief freqMin is the beginning of the signal's bandwidth.
     */
    double freqMin;
    /**
     * @brief freqMax is the end of the signal's bandwidth.
     */
    double freqMax;
    /**
     * @brief operator == compares two transfer functions for equality.
     * @return true iff the transfer functions are equal.
     */
    bool operator ==(const TransferFunction &) const;
};
}

#endif // TRANSFERFUNCTION_H
