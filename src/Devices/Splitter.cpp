#include <Devices/Splitter.h>

Splitter::Splitter(int NumPorts) : NumPorts(NumPorts) ,
	SplitterLoss(1.0 / NumPorts, Gain::init_Linear) {

}

Gain Splitter::get_Gain() {
	return Gain(0);
}

Gain Splitter::get_Loss() {
	return SplitterLoss;
}

Power Splitter::get_Noise() {
	return Power(0, Power::init_Watt);
}
