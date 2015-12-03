#include <assert.h>
#include <cmath>
#include <GeneralClasses/Gain.h>

Gain::Gain(long double value, InitType Type) {
    if (Type == InitType::dB) {
        value_dB = value;
        value_Linear = std::pow(10, 0.1 * value);
    } else if (Type == InitType::Linear) {
		assert(value > 0);
        value_Linear = value;
		value_dB = 10 * log10(value);
    }
}

Gain Gain::operator -() {
	return Gain(-value_dB);
}

Gain::Gain(const Gain &Value) {
    value_dB = Value.in_dB();
    value_Linear = Value.in_Linear();
}

long double Gain::in_dB() const {
    return value_dB;
}

long double Gain::in_Linear() const {
    return value_Linear;
}
