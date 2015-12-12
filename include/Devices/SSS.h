#ifndef SSS_H
#define SSS_H

#include <Devices/Device.h>

/**
 * @brief The SSS class represents a Spectrum Selective Switch.
 */
class SSS : public Device {
  public:
    /**
     * @brief SSSLoss is the loss of a SSS. Is considered constant for all
     * the SSS devices.
     */
    static Gain SSSLoss;

    SSS();

    Gain &get_Gain();
    Power &get_Noise();
    std::shared_ptr<Device> clone();

  private:
    Power NoisePower;
};

#endif // SSS_H
