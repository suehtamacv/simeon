#ifndef DEVICE_H
#define DEVICE_H

#include <GeneralClasses/dB.h>

class Device {
  public:
    virtual dB get_Gain();
    virtual dB get_Loss();
    virtual dB get_Noise();

    Device *Previous;
    Device *Next;
};

#endif // DEVICE_H
