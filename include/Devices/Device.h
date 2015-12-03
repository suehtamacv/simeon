#ifndef DEVICE_H
#define DEVICE_H

#include <GeneralClasses/Gain.h>
#include <GeneralClasses/Power.h>

class Device {
  public:
	Device();
	virtual Gain get_Gain() = 0;
	virtual Gain get_Loss() = 0;
	virtual Power get_Noise() = 0;

    Device *Previous;
    Device *Next;
};

#endif // DEVICE_H
