#ifndef FIBER_H
#define FIBER_H

#include <Devices/Device.h>

/**
 * @brief The Fiber class represents a Fiber segment.
 */
class Fiber : public Device
{
public:
    /**
     * @brief alphaFiber is the fiber loss coefficient, measured in dB per
     * kilometer.
     */
    static double alphaFiber;
    /**
     * @brief Fiber is the constructor for a Fiber device.
     * @param SpanLength is the length of the fiber, in kilometers.
     */
    Fiber(double SpanLength);

    Gain &get_Gain();
    Power &get_Noise();
    double get_CapEx();
    double get_OpEx();

    std::shared_ptr<Device> clone();

private:
    double SpanLength;
    Gain NetLoss;
    Power NoisePower;
};

#endif // FIBER_H
