#include <Calls/Event.h>
#include <iostream>

Event::Event(double t, Event_Type Type, std::shared_ptr<Call> Parent) :
    t(t),
    Type(Type),
    Parent(Parent)
{
#ifdef RUN_ASSERTIONS
    if (t < 0)
        {
        std::cerr << "Occural time should be positive." << std::endl;
        abort();
        }
#endif
}

bool Event::operator >(const Event &E) const
{
    return (t > E.t);
}

bool Event::operator <(const Event &E) const
{
    return (t < E.t);
}

bool Event::operator ==(const Event &E) const
{
    return (t == E.t);
}
