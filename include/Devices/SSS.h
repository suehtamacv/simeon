#ifndef SSS_H
#define SSS_H

#include <Devices/Device.h>

class SSS : public Device {
  public:
	static Gain SSSLoss;
	SSS();

	Gain get_Gain();
	Gain get_Loss();
};

#endif // SSS_H
