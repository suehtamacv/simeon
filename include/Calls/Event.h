#ifndef EVENT_H
#define EVENT_H

#include <memory>

class Call;
class Route;

/**
 * @brief The Event class represents an event that happened in the network. Is
 * either a call requisition or a call ending.
 */
class Event {
  public:
    /**
    * @brief The Event_Type enum is used to specify the type of event.
    *
    * Each call generates two events, a CallRequisition on its start and a
    * CallEnding on its ending.
    */
    enum Event_Type {
        CallRequisition, /*!< Event on the starting call. */
        CallEnding /*!< Event on the ending call. */
    };

    /**
     * @brief Event is the constructor of a Event.
     * @param t is the instant of ocurral of the Event.
     * @param Type is the type of Event.
     */
    Event(long double t, Event_Type Type, std::shared_ptr<Call> Parent);

    /**
     * @brief operator < is used to compare the ocurral instants of two events.
     * @return true iff this event ocurrs prior to the Event passed as argument.
     */
    bool operator<(const Event) const;
    bool operator<(const std::shared_ptr<Event> event);
    /**
     * @brief operator > is used to compare the ocurral instants of two events.
     * @return true iff this event ocurrs after the Event passed as argument.
     */
    bool operator>(const Event) const;

    /**
     * @brief t is the ocurring time of the event.
     */
    long double t;
    Event_Type Type;
    std::shared_ptr<Call> Parent;
    std::shared_ptr<Route> route;
};

#endif // EVENT_H
