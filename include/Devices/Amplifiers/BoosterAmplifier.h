#ifndef BOOSTERAMPLIFIER_H
#define BOOSTERAMPLIFIER_H

#include <Devices/Amplifiers/Amplifier.h>

class BoosterAmplifier : public Amplifier {
  public:
	static constexpr AmplifierType AT = Amplifier::BoosterAmplifierType;
	BoosterAmplifier(Gain G);
};

#endif // BOOSTERAMPLIFIER_H
