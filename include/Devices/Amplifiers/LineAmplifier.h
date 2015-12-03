#ifndef LINEAMPLIFIER_H
#define LINEAMPLIFIER_H

#include <Devices/Amplifiers/Amplifier.h>

class Fiber;

class LineAmplifier : public Amplifier {
  public:
	static constexpr AmplifierType AT = Amplifier::LineAmplifierType;
	LineAmplifier(Fiber &Segment);

	Gain get_Gain();
};

#endif // LINEAMPLIFIER_H
