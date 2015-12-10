#include <Calls/Event.h>

Event::Event(long double t, Event_Type Type, std::shared_ptr<Call> Parent) :
    t(t),
    Type(Type),
    Parent(Parent) {
}

bool Event::operator <(const Event E) const {
    if (t > E.t) {
        return true;
    }

    return false;
}

bool Event::operator<(std::shared_ptr<Event> event) {
    if (t > event->t) {
        return true;
    }

    return false;
}
