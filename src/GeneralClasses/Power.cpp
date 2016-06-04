#include <GeneralClasses/Power.h>
#include <cmath>
#include <gtest/gtest.h>

Power::Power(double value, InitType Type)
{
    if (Type == InitType::dBm)
        {
        value_Watts = 0.001L * pow(10, 0.1 * value);
        }
    else if (Type == InitType::Watt)
        {
        EXPECT_GE(value , 0) << "A power, in Watts, can't be negative.";
        value_Watts = value;
        }
}

Power::Power(const Power &Value)
{
    value_Watts = Value.in_Watts();
}

Power Power::operator *(Gain G)
{
    return Power(value_Watts * G.in_Linear(), Power::Watt);
}

Power &Power::operator *=(Gain &G)
{
    value_Watts *= G.in_Linear();
    return *this;
}

Power Power::operator +(Power &P)
{
    return Power(value_Watts + P.in_Watts(), Power::Watt);
}

Power &Power::operator +=(Power &P)
{
    value_Watts += P.in_Watts();
    return *this;
}

double Power::in_dBm() const
{
    return 10 * log10(value_Watts) + 30;
}

double Power::in_Watts() const
{
    return value_Watts;
}

bool Power::operator <(const Power &P) const
{
    return value_Watts < P.value_Watts;
}

double Power::operator /(const Power &P) const
{
    return value_Watts / P.value_Watts;
}
