#include <Devices/SSS.h>

Gain SSS::SSSLoss(-5);

SSS::SSS() : Device(Device::SSSDevice), NoisePower(0, Power::Watt) {

}

Gain &SSS::get_Gain() {
    return SSSLoss;
}

Power &SSS::get_Noise() {
    return NoisePower;
}

std::shared_ptr<Device> SSS::clone() {
    return std::shared_ptr<Device>(new SSS(*this));
}
