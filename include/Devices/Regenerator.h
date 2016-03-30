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
    /**
     * @brief get_TransferFunction returns the transfer function that represents the device's frequency response.
     * @param numSlots is the number of slots used to calculate the transfer function.
     * @return the transfer function that represents the device's frequency response.
     */
    TransferFunction &get_TransferFunction(unsigned int numSlots);
    double get_CapEx();
    double get_OpEx();

    std::shared_ptr<Device> clone();

private:
    Gain RegeneratorGain;
    Power RegeneratorNoise;
    /**
     * @brief deviceTF  is this device's transfer function.
     */
    std::shared_ptr<TransferFunction> deviceTF;
};
}

#endif // REGENERATOR_H
