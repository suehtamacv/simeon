#ifndef BOOSTERAMPLIFIER_H
#define BOOSTERAMPLIFIER_H

#include <Devices/Amplifiers/EDFA.h>

class BoosterAmplifier : public EDFA {
  public:
    static constexpr AmplifierType AT = Amplifier::BoosterAmplifierType;
    BoosterAmplifier();

    Gain get_Gain();
};

#endif // BOOSTERAMPLIFIER_H
