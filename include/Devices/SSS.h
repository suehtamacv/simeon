#ifndef SSS_H
#define SSS_H

#include <Devices/Device.h>
#include <map>

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
    TransferFunction &get_TransferFunction(unsigned int numSlots);
    double get_CapEx();
    double get_OpEx();

    std::shared_ptr<Device> clone();
    unsigned int filterOrder;

private:
    Power NoisePower;
    Node *parent;
    std::map<int, TransferFunction> transFunctionsCache;
};

#endif // SSS_H
