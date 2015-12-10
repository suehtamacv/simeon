#include <Devices/Splitter.h>

Splitter::Splitter(int NumPorts) : Device(Device::SplitterDevice),
    NumPorts(NumPorts), SplitterLoss(1.0 / (NumPorts + 1), Gain::Linear) {
}

Gain Splitter::get_Gain() {
    return SplitterLoss;
}

Power Splitter::get_Noise() {
    return Power(0, Power::Watt);
}

void Splitter::set_NumPorts(int NumPorts) {
    this->NumPorts = NumPorts;
    SplitterLoss = Gain(1.0 / (NumPorts + 1), Gain::Linear);
}

std::shared_ptr<Device> Splitter::clone() {
    return std::shared_ptr<Device>(new Splitter(*this));
}
