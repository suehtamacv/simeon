#ifndef SPLITTER_H
#define SPLITTER_H

#include <Devices/Device.h>

class Node;

namespace Devices
{
/**
 * @brief The Splitter class represents a splitter. Is only used with the
 * Broadcast-And-Select node architecture.
 */
class Splitter : public Device
{
public:
    /**
     * @brief Splitter is the standard constructor for a splitter.
     * @param NumPorts is the number of ports of the splitter.
     */
    Splitter(Node *parent);

    Gain &get_Gain();
    Power &get_Noise();
    /**
     * @brief get_TransferFunction returns the transfer function that represents the device's frequency response.
     * @param numSlots is the number of slots used to calculate the transfer function.
     * @return the transfer function that represents the device's frequency response.
     */
    TransferFunction &get_TransferFunction(unsigned int numSlots);
    double get_CapEx();
    double get_OpEx();

    std::shared_ptr<Device> clone();

    /**
     * @brief set_NumPorts is used to reconfigure the number of ports of this
     * Splitter. Is called, for example, when a new link is added to the owner Node.
     * @param NumPorts is the new number of ports of this Splitter.
     */
    void set_NumPorts(int NumPorts);

private:
    Node *parent;
    unsigned int NumPorts;
    Gain SplitterLoss;
    Power NoisePower;
    /**
     * @brief deviceTF  is the device's transfer function.
     */
    std::shared_ptr<TransferFunction> deviceTF;
};
}

#endif // SPLITTER_H
