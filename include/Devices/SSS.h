#ifndef SSS_H
#define SSS_H

#include <Devices/Device.h>

class SSS : public Device {
  public:
	static dB SSSLoss;
	SSS();

	dB get_Gain();
	dB get_Loss();
	dB get_Noise();
};

#endif // SSS_H
