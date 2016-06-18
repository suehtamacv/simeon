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
    std::shared_ptr<TF::Transmittance> get_TransferFunction(double centerFreq);
    double get_CapEx();
    double get_OpEx();

    /**
     * @brief get_TransferFunction returns the transfer function that represents the device's blocking frequency response.
     * @param centerFreq is the central frequency of this transfer function.
     * @return the transfer function that represents the device's frequency response.
     */
    std::shared_ptr<TF::Transmittance> get_BlockTransferFunction(double centerFreq);

    std::shared_ptr<Device> clone();
    /**
     * @brief filterOrder is the order of the optical filter in this device.
     */
    unsigned int filterOrder;

private:
    Power NoisePower;
    Node *parent;
    /**
     * @brief deviceTF is the device's transfer function.
     */
    std::shared_ptr<TF::Transmittance> deviceTF;
    /**
     * @brief bypassFunctionsCache is a map of the transfer functions of this
     * SSS device, given a certain central frequency and bandwidth.
     */
    std::map<double, std::shared_ptr<TF::Transmittance>> bypassFunctionsCache;
    /**
     * @brief blockingFunctionsCache is a map of the blocking transfer functions
     *  of this SSS device, given a certain central frequency and bandwidth.
     */
    std::map<double, std::shared_ptr<TF::Transmittance>> blockingFunctionsCache;
};
}

#endif // SSS_H
