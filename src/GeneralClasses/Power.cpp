#include <assert.h>
#include <cmath>
#include <GeneralClasses/Power.h>

Power::Power(long double value, InitType Type) {
	if (Type == InitType::init_dBm) {
		value_dBm = value;
		value_Watts = 0.001L * pow(10, 0.1 * value);
	} else if (Type == InitType::init_Watt) {
		assert(value >= 0);
		value_Watts = value;
		value_dBm = 10 * log10(value) + 30;
	}
}

Power Power::operator *(Gain G) {
	return Power(G.in_dB() + value_dBm);
}

long double Power::in_dBm() const {
	return value_dBm;
}

long double Power::in_Watts() const {
	return value_Watts;
}
