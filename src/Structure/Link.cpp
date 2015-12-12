#include <boost/assert.hpp>
#include <cmath>
#include <Calls/Call.h>
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

Link::Link(const Link &link) {
    Length = link.Length;
    Origin = link.Origin;
    Destination = link.Destination;

    for (auto slot : link.Slots) {
        Slots.push_back(std::shared_ptr<Slot>(new Slot(*slot)));
    }

    for (auto device : link.Devices) {
        Devices.push_back(device->clone());
    }
}

void Link::create_Slots() {
    for (int i = 0; i < NumSlots; i++) {
        Slots.push_back(std::shared_ptr<Slot>(new Slot(i)));
    }
}

void Link::create_Devices() {
    numLineAmplifiers = floor(Length / AvgSpanLength);

    if (ceil(Length / AvgSpanLength) == numLineAmplifiers) {
        numLineAmplifiers--;
    }

    long double SpanLength = Length / (numLineAmplifiers + 1);

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

Signal &Link::bypass(Signal &S) {
    for (auto it : Devices) {
        S *= it->get_Gain();
        S += it->get_Noise();
    }

    return S;
}

bool Link::operator ==(const Link &L) const {
    return ((Origin.lock() == L.Origin.lock()) &&
            (Destination.lock() == L.Destination.lock()) &&
            (Length == L.Length));
}

bool Link::operator <(const Link &L) const {
    return ((Origin.lock() < L.Origin.lock()) ||
            (Destination.lock() < L.Destination.lock()) ||
            (Length < L.Length));
}

bool Link::isSlotFree(unsigned int slot) const {
    BOOST_ASSERT_MSG(slot < NumSlots, "Invalid slot requested.");
    return (Slots[slot])->isFree;
}

long double Link::get_Availability() {
    long double FreeSlots = 0;

    for (auto slot : Slots) {
        if (slot->isFree) {
            FreeSlots++;
        }
    }

    return FreeSlots / Link::NumSlots;
}

long double Link::get_Occupability() {
    return 1 - get_Availability();
}

long double Link::get_Contiguity(std::shared_ptr<Call> C) {
    BOOST_ASSERT_MSG(C->Scheme.get_M() != 0,
                     "Can't calculate contiguity without knowing the modulation"
                     " scheme. Either you forgot to set it or one of the chosen "
                     "algorithms is not compatible with the contiguity measure");
    int NumRequiredSlots = C->Scheme.get_NumSlots(C->Bitrate);
    int Contiguity = 0;
    int si = 0;
    bool SlotsAvailability[Link::NumSlots];

    for (int i = 0; i < Link::NumSlots; i++) {
        SlotsAvailability[i] = Slots[i]->isFree;
    }

    for (si = 0; si <= Link::NumSlots - NumRequiredSlots; si++) {
        int slot;

        for (slot = si; slot < si + NumRequiredSlots; slot++) {
            if (!SlotsAvailability[slot]) {
                break;
            }

            if (slot == si + NumRequiredSlots) {
                Contiguity++;
            }
        }
    }

    return Contiguity;
}
