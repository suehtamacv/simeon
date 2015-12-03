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

    Gain get_Gain();
    Gain get_Loss();
	Power get_Noise();

  private:
    long double SpanLength;
    Gain NetLoss;
};

#endif // FIBER_H
