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
    * @brief Call is the standard constructor for a Call object.
    * @param Origin is a weak_ptr for the Origin node.
    * @param Destination is a weak_ptr for the Destination node.
    * @param Bitrate is a TransmissionBitrate.
    */
    Call(std::weak_ptr<Node> Origin,
         std::weak_ptr<Node> Destination,
         TransmissionBitrate Bitrate);

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
};

#endif // CALL_H
