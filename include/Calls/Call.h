#ifndef CALL_H
#define CALL_H

#include <memory>
#include <GeneralClasses/TransmissionBitrate.h>
#include <GeneralClasses/ModulationScheme.h>

class Node;
class Event;

/**
 * @brief The Call class is the standard object representing a connection
 * between two nodes.
 */
class Call
{
public:
    /**
     * @brief The Call_Status enum is used to describe the current status
     * of the call.
     */
    enum Call_Status
    {
        Implemented, /*!< The RWA algorithm succeeded to find a route */
        Blocked, /*!< The RWA algorithm could not find a route to stablish the call */
        Not_Evaluated /*!< The RWA algorithm is running / will run over the call */
    };
    /**
     * @brief The BlockingReason enum is used to specify the reason why the call
     * was blocked
     */
    enum BlockingReason
    {
        Blocking_Route = 0x01,
        Blocking_Spectrum = 0x02, /*!< There was not enough spectrum to implement the call */
        Blocking_ASE_Noise = 0x04, /*!< There OSNR was too low to implement the call */
        Blocking_FilterImperfection = 0x08 /*!< The power ratio due to the filter imperfection was too low */
    };

    /**
    * @brief Call is the standard constructor for a Call object.
    * @param Origin is a weak_ptr for the Origin node.
    * @param Destination is a weak_ptr for the Destination node.
    * @param Bitrate is a TransmissionBitrate.
    */
    Call(std::weak_ptr<Node> Origin,
         std::weak_ptr<Node> Destination,
         TransmissionBitrate Bitrate);
    /**
    * @brief Call is the standard constructor for a Call object.
    * @param Origin is a weak_ptr for the Origin node.
    * @param Destination is a weak_ptr for the Destination node.
    * @param Bitrate is a TransmissionBitrate.
    * @param Scheme is the ModulationScheme.
    */
    Call(std::weak_ptr<Node> Origin,
         std::weak_ptr<Node> Destination,
         TransmissionBitrate Bitrate,
         ModulationScheme Scheme);

    /**
     * @brief CallRequisition is a pointer to the requisition event.
     */
    std::weak_ptr<Event> CallRequisition;
    /**
     * @brief CallEnding is a pointer to the ending event.
     */
    std::weak_ptr<Event> CallEnding;
    /**
     * @brief Origin is a pointer to the origin node.
     */
    std::weak_ptr<Node> Origin;
    /**
     * @brief Destination is a pointer to the destination node.
     */
    std::weak_ptr<Node> Destination;
    /**
     * @brief Bitrate is a Transmission Bitrate.
     */
    TransmissionBitrate Bitrate;
    /**
     * @brief Status is the current status of the Call.
     */
    Call_Status Status;
    /**
     * @brief Scheme is the modulation scheme used to stablish the connection,
     * when applicable.
     *
     * This parameter only contains useful information when simulating transparent
     * networks. In translucent networks, more than one scheme can be used and this
     * parameter is not useful. Note that some algorithms, such as Length and Occu-
     * pation Routing Contiguity require this parameter. This means that this routing
     * algorithm is incompatible with translucent networks.
     */
    ModulationScheme Scheme;
    /**
     * @brief blockingReason specifies the reason why the call was blocked.
     */
    uint8_t blockingReason;
};

#endif // CALL_H
