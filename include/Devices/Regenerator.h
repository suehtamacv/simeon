#ifndef REGENERATOR_H
#define REGENERATOR_H

#include "Device.h"

namespace Devices
{
/**
 * @brief The Regenerator class represents a electronic regenerator.
 */
class Regenerator : public Device
{
public:
    /**
     * @brief Regenerator is the constructor for a regenerator device.
     */
    Regenerator();

    Gain &get_Gain();
    Power &get_Noise();
    std::shared_ptr<TF::Transmittance> get_TransferFunction(double);
    double get_CapEx();
    double get_OpEx();

    std::shared_ptr<Device> clone();

private:
    Gain RegeneratorGain;
    Power RegeneratorNoise;
    /**
     * @brief deviceTF  is the device's transfer function.
     */
    std::shared_ptr<TF::Transmittance> deviceTF;
};
}

#endif // REGENERATOR_H
