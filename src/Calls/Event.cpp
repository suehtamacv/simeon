#include <Calls/Event.h>

Event::Event(double t, Event_Type Type, std::shared_ptr<Call> Parent) :
    t(t),
    Type(Type),
    Parent(Parent) {
}

bool Event::operator >(const Event &E) const {
    return (t > E.t);
}
