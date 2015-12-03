#include <Calls/Event.h>

Event::Event(long double t, Event_Type Type,
             std::shared_ptr<Call> Parent) : t(t) , Type(Type), Parent(Parent) {

}

bool Event::operator <(Event E) {
    if (t < E.t) {
        return true;
    }

    return false;
}
