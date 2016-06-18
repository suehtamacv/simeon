#ifndef CONSTANTTRANSMITTANCE_H
#define CONSTANTTRANSMITTANCE_H

#include "Transmittance.h"

namespace TF
{
class ConstantTransmittance : public Transmittance
{
public:
    ConstantTransmittance(Gain scale);

    Gain get_TransmittanceAt(double);
};
}

#endif // CONSTANTTRANSMITTANCE_H
