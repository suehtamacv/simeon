#ifndef EVENT_H
#define EVENT_H

#include <memory>

class Call;

namespace RMSA
{
class Route;
}

/**
 * @brief The Event class represents an event that happened in the network. Is
 * either a call requisition or a call ending.
 */
class Event
{
public:
    /**
    * @brief The Event_Type enum is used to specify the type of event.
    *
    * Each call generates two events, a CallRequisition on its start and a
    * CallEnding on its ending.
    */
    enum Event_Type
    {
        CallRequisition, /*!< Event on the starting call. */
        CallEnding /*!< Event on the ending call. */
    };

    /**
     * @brief Event is the constructor of a Event.
     * @param t is the instant of ocurral of the Event.
     * @param Type is the type of Event.
     * @param Parent if a pointer to the owner Call of this Event.
     */
    Event(double t, Event_Type Type, std::shared_ptr<Call> Parent);

    /**
     * @brief operator > is used to compare the ocurral instants of two events.
     * @return true iff this event ocurrs after the Event passed as argument.
     */
    bool operator>(const Event &) const;
    /**
     * @brief operator < is used to compare the ocurral instants of two events.
     * @return true iff this event ocurrs before the Event passed as argument.
     */
    bool operator<(const Event &) const;

    /**
     * @brief t is the ocurring time of the event.
     */
    double t;
    /**
     * @brief Type is the type of Event.
     */
    Event_Type Type;
    /**
     * @brief Parent is a pointer to the Call that owns this Event.
     */
    std::shared_ptr<Call> Parent;
    /**
     * @brief route is a pointer to the Route used to stablish the Parent Call.
     * If did not succeeded to stablish, then this is a pointer to nullptr.
     */
    std::shared_ptr<RMSA::Route> route;
};

#endif // EVENT_H
