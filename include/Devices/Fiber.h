#ifndef FIBER_H
#define FIBER_H

#include <Devices/Device.h>

class Fiber : public Device {
  public:
    /**
     * @brief alphaFiber is the fiber loss coefficient, measured in dB per kilometer.
     */
    static long double alphaFiber;
    /**
     * @brief Fiber is the constructor for a Fiber device.
     * @param SpanLength is the length of the fiber, in kilometers.
     */
    Fiber(long double SpanLength);

    dB get_Gain();
    dB get_Loss();
    dB get_Noise();

  private:
    long double SpanLength;
    dB NetLoss;
};

#endif // FIBER_H
