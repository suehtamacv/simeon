#include <assert.h>
#include <cmath>
#include <Structure/Link.h>

long double Link::AvgSpanLength = 80;

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
	int num_LineAmplifiers = floor(Length / AvgSpanLength);

	if (ceil(Length / AvgSpanLength) == num_LineAmplifiers) {
		num_LineAmplifiers--;
	}

	long double SpanLength = Length / num_LineAmplifiers;

	//Each line amplifier compensates for the loss in the previous fiber segment.
	Gain AmplGain(SpanLength * Fiber::alphaFiber);

	for (int i = 0; i < num_LineAmplifiers; i++) {
		Devices.push_back(std::unique_ptr<Amplifier>(new Amplifier(AmplGain)));
		Devices.push_back(std::unique_ptr<Fiber>(new Fiber(SpanLength)));
	}
}
