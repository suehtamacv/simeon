#ifndef CALL_H
#define CALL_H

#include <memory>
#include <Calls/Event.h>
#include <GeneralClasses/TransmissionBitrate.h>

class Node;

/**
 * @brief The Call class is the standard object representing a connection
 * between two nodes.
 */
class Call {
  public:
    enum Call_Status {
        Implemented,
        Blocked,
        Not_Evaluated
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
    Call_Status Status;
};

#endif // CALL_H
