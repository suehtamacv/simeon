#include <boost/assert.hpp>
#include <cmath>
#include <GeneralClasses/Power.h>

Power::Power(long double value, InitType Type) {
    if (Type == InitType::dBm) {
        value_dBm = value;
        value_Watts = 0.001L * pow(10, 0.1 * value);
    } else if (Type == InitType::Watt) {
        BOOST_ASSERT_MSG(value >= 0, "A power, in Watts, can't be negative.");
        value_Watts = value;
        value_dBm = 10 * log10(value) + 30;
    }
}

Power::Power(const Power &Value) {
    value_dBm = Value.in_dBm();
    value_Watts = Value.in_Watts();
}

Power Power::operator *(Gain G) {
    return Power(G.in_dB() + value_dBm);
}

void Power::operator *=(Gain G) {
    value_dBm += G.in_dB();
    value_Watts = 0.001L * pow(10, 0.1 * value_dBm);
}

Power Power::operator +(Power P) {
    return Power(value_Watts + P.in_Watts(), Power::Watt);
}

void Power::operator +=(Power P) {
    value_Watts += P.in_Watts();
    value_dBm = 10 * log10(value_Watts) + 30;
}

long double Power::in_dBm() const {
    return value_dBm;
}

long double Power::in_Watts() const {
    return value_Watts;
}
