#ifndef EVENT_H
#define EVENT_H

#include <memory>

class Call;

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
     * @param Parent is the Call that owns this Event.
     */
    Event(long double t, Event_Type Type, Call *Parent);

    /**
     * @brief operator < is used to compare the ocurral instants of two events.
     * @return true iff this event ocurrs prior to the Event passed as argument.
     */
    bool operator<(const Event) const;
    /**
     * @brief operator > is used to compare the ocurral instants of two events.
     * @return true iff this event ocurrs after the Event passed as argument.
     */
    bool operator>(const Event) const;

    long double t;
    Event_Type Type;
    Call *Parent;
};

#endif // EVENT_H
