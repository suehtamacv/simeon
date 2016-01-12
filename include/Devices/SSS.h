#ifndef SSS_H
#define SSS_H

#include <Devices/Device.h>

class Node;

/**
 * @brief The SSS class represents a spectrum selective switch.
 */
class SSS : public Device
{
public:
    /**
     * @brief SSSLoss is the loss of a SSS. Is considered constant for all
     * the SSS devices.
     */
    static Gain SSSLoss;
    /**
     * @brief SSS is the standard constructor of a SSS.
     */
    SSS(Node *parent);

    Gain &get_Gain();
    Power &get_Noise();
    double get_CapEx();
    double get_OpEx();

    std::shared_ptr<Device> clone();

private:
    Power NoisePower;
    Node *parent;
};

#endif // SSS_H
