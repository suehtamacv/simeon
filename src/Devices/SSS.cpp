#include <Devices/SSS.h>

Gain SSS::SSSLoss(-5);

SSS::SSS() : Device(Device::SSSDevice) {

}

Gain SSS::get_Gain() {
    return SSSLoss;
}

Power SSS::get_Noise() {
    return Power(0, Power::Watt);
}
