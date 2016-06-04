#include <Calls/Event.h>
#include <gtest/gtest.h>

Event::Event(double t, Event_Type Type, std::shared_ptr<Call> Parent) :
    t(t),
    Type(Type),
    Parent(Parent)
{
    EXPECT_GE(t, 0) << "Occural time should be positive.";
}

bool Event::operator >(const Event &E) const
{
    return (t > E.t);
}

bool Event::operator <(const Event &E) const
{
    return (t < E.t);
}
