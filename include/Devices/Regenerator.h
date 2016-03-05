#ifndef REGENERATOR_H
#define REGENERATOR_H

#include "Device.h"

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
    TransferFunction &get_TransferFunction(unsigned int numSlots);
    double get_CapEx();
    double get_OpEx();

    std::shared_ptr<Device> clone();

private:
    Gain RegeneratorGain;
    Power RegeneratorNoise;
    std::shared_ptr<TransferFunction> deviceTF;
};

#endif // REGENERATOR_H
