#include <Devices/SSS.h>

dB SSS::SSSLoss = dB(-5, dB::init_dB);

SSS::SSS() {

}

dB SSS::get_Gain() {
	return dB(0);
}

dB SSS::get_Loss() {
	return SSSLoss;
}

dB SSS::get_Noise() {
	return dB(0, dB::init_Linear);
}
