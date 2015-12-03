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

	for (int i = 0; i < numLineAmplifiers; i++) {
		Devices.push_back(std::unique_ptr<Fiber>(new Fiber(SpanLength)));
		Devices.push_back(std::unique_ptr<LineAmplifier>(
							  new LineAmplifier((Fiber &)*Devices.back())));
	}

	//There's an extra fiber segment in the end of the link
	Devices.push_back(std::unique_ptr<Fiber>(new Fiber(SpanLength)));

	//There's a preamplifier in the node's entrance.
	//It compensates the fiber segment loss and also the switching element loss.
	Devices.push_back(std::unique_ptr<PreAmplifier>(new PreAmplifier((
						  Fiber &)*Devices.back(), *Destination.lock())));
}

Signal Link::cross(Signal S) {
	for (auto it = Devices.begin(); it != Devices.end(); ++it) {
		S *= (*it)->get_Gain();
		S *= (*it)->get_Loss();
		S += (*it)->get_Noise();
	}

	return S;
}
