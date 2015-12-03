#ifndef PREAMPLIFIER_H
#define PREAMPLIFIER_H

#include <Devices/Amplifiers/Amplifier.h>

class PreAmplifier : public Amplifier {
  public:
	static constexpr AmplifierType AT = Amplifier::PreAmplifierType;
	PreAmplifier(Gain G);
};

#endif // PREAMPLIFIER_H
