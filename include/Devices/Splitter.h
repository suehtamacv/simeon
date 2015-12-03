#ifndef SPLITTER_H
#define SPLITTER_H

#include <Devices/Device.h>

class Splitter : public Device {
  public:
	static constexpr DeviceType T = Device::SplitterDevice;

	Splitter(int NumPorts);

	Gain get_Gain();
	Gain get_Loss();
	Power get_Noise();

  private:
	int NumPorts;
	Gain SplitterLoss;
};

#endif // SPLITTER_H
