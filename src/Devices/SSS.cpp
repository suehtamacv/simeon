#include <Devices/SSS.h>

Gain SSS::SSSLoss(-5);

SSS::SSS() {

}

Gain SSS::get_Gain() {
	return Gain(0);
}

Gain SSS::get_Loss() {
	return SSSLoss;
}

Power SSS::get_Noise() {
	return Power(0, Power::Watt);
}
