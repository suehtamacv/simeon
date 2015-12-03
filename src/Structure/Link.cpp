#include <assert.h>
#include <cmath>
#include <Structure/Link.h>

Link::Link(std::weak_ptr<Node> Origin,
		   std::weak_ptr<Node> Destination,
		   long double Length) {

	assert(Length >= 0);
	this->Origin = Origin;
	this->Destination = Destination;
	this->Length = Length;

	create_Slots();
	create_Devices();
}

void Link::create_Slots() {
	for (int i = 0; i < NumSlots; i++) {
		Slots.push_back(std::unique_ptr<Slot>(new Slot(i, this)));
	}
}

void Link::create_Devices() {
	numLineAmplifiers = floor(Length / AvgSpanLength);

	if (ceil(Length / AvgSpanLength) == numLineAmplifiers) {
		numLineAmplifiers--;
	}

	long double SpanLength = Length / numLineAmplifiers;

	//Each line amplifier compensates for the loss in the previous fiber segment.
	Gain AmplGain(SpanLength * Fiber::alphaFiber);

	for (int i = 0; i < numLineAmplifiers; i++) {
		Devices.push_back(std::unique_ptr<Amplifier>(new Amplifier(AmplGain)));
		Devices.push_back(std::unique_ptr<Fiber>(new Fiber(SpanLength)));
	}
}

Signal Link::cross_Link(Signal S) {
	for (auto it = Devices.begin(); it != Devices.end(); ++it) {
		S *= (*it)->get_Gain();
		S *= (*it)->get_Loss();
		S += (*it)->get_Noise();
	}

	return S;
}
