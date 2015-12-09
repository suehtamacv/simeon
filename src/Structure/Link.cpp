#include <boost/assert.hpp>
#include <cmath>
#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <Devices/Fiber.h>
#include <Devices/Amplifiers/InLineAmplifier.h>
#include <Devices/Amplifiers/PreAmplifier.h>

Link::Link(std::weak_ptr<Node> Origin,
           std::weak_ptr<Node> Destination,
           long double Length) {

    BOOST_ASSERT_MSG(Length >= 0, "Length can't be negative.");
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
        Devices.push_back(std::shared_ptr<Fiber>(new Fiber(SpanLength)));
        Devices.push_back(std::shared_ptr<InLineAmplifier>(
                              new InLineAmplifier((Fiber &)*Devices.back())));
    }

    //There's an extra fiber segment in the end of the link
    Devices.push_back(std::shared_ptr<Fiber>(new Fiber(SpanLength)));

    //There's a preamplifier in the node's entrance.
    //It compensates the fiber segment loss and also the switching element loss.
    Devices.push_back(std::shared_ptr<PreAmplifier>(new PreAmplifier((
                          Fiber &)*Devices.back(), *Destination.lock())));
}

Signal Link::bypass(Signal S) {
    for (auto it = Devices.begin(); it != Devices.end(); ++it) {
        S *= (*it)->get_Gain();
        S += (*it)->get_Noise();
    }

    return S;
}

bool Link::operator ==(Link *L) const {
    if (Origin.lock() != L->Origin.lock()) {
        return false;
    }

    if (Destination.lock() != L->Destination.lock()) {
        return false;
    }

    if (Length != L->Length) {
        return false;
    }

    return true;
}

bool Link::operator <(Link *L) const {
    if (Origin.lock() < L->Origin.lock()) {
        return true;
    }

    if (Destination.lock() < L->Destination.lock()) {
        return true;
    }

    if (Length < L->Length) {
        return true;
    }

    return false;
}

bool Link::isSlotFree(unsigned int slot) const {
    BOOST_ASSERT_MSG(slot < NumSlots, "Invalid slot requested.");
    return (Slots[slot])->isFree;
}
