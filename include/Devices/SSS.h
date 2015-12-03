#ifndef SSS_H
#define SSS_H

#include <Devices/Device.h>

class SSS : public Device {
  public:
	SSS();

	Gain get_Gain();
	Gain get_Loss();
	Power get_Noise();

  private:
	static Gain SSSLoss;
};

#endif // SSS_H
