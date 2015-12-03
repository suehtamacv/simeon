#include <Devices/SSS.h>

Gain SSS::SSSLoss = Gain(-5);

SSS::SSS() {

}

Gain SSS::get_Gain() {
	return Gain(0);
}

Gain SSS::get_Loss() {
	return SSSLoss;
}
