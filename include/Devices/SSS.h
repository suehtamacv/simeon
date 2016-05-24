#ifndef SSS_H
#define SSS_H

#include <Devices/Device.h>
#include <map>

class Node;
class Link;
class SpectralDensity;

namespace Devices
{
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
    /**
     * @brief get_TransferFunction returns the transfer function that represents the device's frequency response.
     * @param numSlots is the number of slots used to calculate the transfer function.
     * @return the transfer function that represents the device's frequency response.
     */
    TF::TransferFunction &get_TransferFunction(unsigned int numSlots);
    double get_CapEx();
    double get_OpEx();

    std::shared_ptr<Device> clone();
    /**
     * @brief filterOrder is the order of the optical filter in this device.
     */
    unsigned int filterOrder;
    /**
     * @brief bypassFunctionsCache is a map of the transfer functions of this
     * SSS device, given a certain number of slots.
     */
    std::map<int, TF::TransferFunction> bypassFunctionsCache;
    /**
     * @brief blockingFunctionsCache is a map of the blocking transfer functions
     *  of this SSS device, given a certain number of slots.
     */
    std::map<int, TF::TransferFunction> blockingFunctionsCache;

private:
    Power NoisePower;
    Node *parent;
    /**
     * @brief deviceTF  is the device's transfer function.
     */
    std::shared_ptr<TF::TransferFunction> deviceTF;
};
}

#endif // SSS_H