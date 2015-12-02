#ifndef DEVICE_H
#define DEVICE_H

#include <GeneralClasses/dB.h>

class Device {
  public:
	virtual dB get_Gain() = 0;
	virtual dB get_Loss() = 0;
	virtual dB get_Noise() = 0;

    Device *Previous;
    Device *Next;
};

#endif // DEVICE_H
