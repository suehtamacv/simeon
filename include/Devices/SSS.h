#ifndef SSS_H
#define SSS_H

#include <Devices/Device.h>

class SSS : public Device {
  public:
	static constexpr DeviceType T = Device::SSSDevice;
	static Gain SSSLoss;

	SSS();

	Gain get_Gain();
	Gain get_Loss();
	Power get_Noise();
};

#endif // SSS_H
