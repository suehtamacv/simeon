#ifndef SIGNAL_H
#define SIGNAL_H

#include <GeneralClasses/Power.h>

/**
 * @brief The Signal class represents a signal that propagates through the
 * network.
 */
class Signal {
  public:

    static Gain InputOSNR;
    static Power InputPower;

    Signal();

    Signal &operator *=(Gain);
    Signal &operator +=(Power);

    Gain get_OSNR();

  private:
    Power SignalPower;
    Power NoisePower;
};

#endif // SIGNAL_H
