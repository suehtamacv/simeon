#include <boost/assert.hpp>
#include <cmath>
#include <GeneralClasses/Gain.h>

Gain::Gain(long double value, InitType Type) : value_Linear(0),
    calculatedLinear(false) {

    if (Type == InitType::dB) {
        value_dB = value;
    } else if (Type == InitType::Linear) {
        BOOST_ASSERT_MSG(value > 0, "There's no dB value for something negative.");
        value_dB = 10 * log10(value);
    }

}

Gain Gain::operator -() {
    return Gain(-value_dB);
}

Gain Gain::operator +(Gain &G) {
    return Gain(value_dB + G.in_dB());
}

Gain Gain::operator -(Gain &G) {
    return Gain(value_dB - G.in_dB());
}

Gain::Gain(const Gain &Value) {
    value_dB = Value.in_dB();

    if (Value.calculatedLinear) {
        value_Linear = Value.value_Linear;
        calculatedLinear = true;
    } else {
        calculatedLinear = false;
    }
}

long double Gain::in_dB() const {
    return value_dB;
}

long double Gain::in_Linear() {
    if (!calculatedLinear) {

        value_Linear = pow10(0.1 * value_dB);
        calculatedLinear = true;
    }

    return value_Linear;
}

bool Gain::operator >(const Gain &G) const {
    return (value_dB > G.in_dB());
}

bool Gain::operator <(const Gain &G) const {
    return (value_dB < G.in_dB());
}

bool Gain::operator ==(const Gain &G) const {
    return (value_dB == G.in_dB());
}
