#ifndef TRANSMITTANCE_H
#define TRANSMITTANCE_H

#include <armadillo>
#include <vector>
#include "include/GeneralClasses/Gain.h"


//! Contains models for the transmittance of optical devices.
namespace TF
{
/**
 * @brief The Transmittance class represents a transmittance of an optical device.
 */
class Transmittance
{
public:
    /**
     * @brief Transmittance is a constructor for a Transmittance.
     * @param scale is the result of the gains and losses over this transmittance.
     */
    Transmittance(Gain scale);
    /**
     * @brief get_TransmittanceAt returns the value of this transmittance at
     * a frequency @param freq.
     * @param freq is the frequency where the transmittance is calculated.
     * @return the value of the transmittance at @param freq.
     */
    virtual Gain get_TransmittanceAt(double freq) = 0;

protected:
    /**
     * @brief scale is the result of the gains and losses over this transmittance.
     */
    Gain scale;
};
}

#endif // TRANSMITTANCE_H
