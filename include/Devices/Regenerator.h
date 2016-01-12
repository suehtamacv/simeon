#ifndef REGENERATOR_H
#define REGENERATOR_H

#include "Device.h"

class Regenerator : public Device
{
public:
    Regenerator();

    Gain &get_Gain();
    Power &get_Noise();
    double get_CapEx();
    double get_OpEx();

    std::shared_ptr<Device> clone();

private:
    Gain RegeneratorGain;
    Power RegeneratorNoise;
};

#endif // REGENERATOR_H
