#include <boost/assert.hpp>
#include <cmath>
#include <Calls/Call.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <Devices/Fiber.h>
#include <Devices/Amplifiers/InLineAmplifier.h>
#include <Devices/Amplifiers/PreAmplifier.h>

int Link::NumSlots = 64;
double Link::AvgSpanLength;

Link::Link(std::weak_ptr<Node> Origin,
           std::weak_ptr<Node> Destination,
           double Length) {

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

    for (auto &slot : link.Slots) {
        Slots.push_back(std::shared_ptr<Slot>(new Slot(*slot)));
    }

    for (auto &device : link.Devices) {
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

    double SpanLength = Length / (numLineAmplifiers + 1);

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
    for (auto &it : Devices) {
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

bool Link::isSlotFree(int slot) const {
    BOOST_ASSERT_MSG(slot < NumSlots, "Invalid slot requested.");
    return (Slots[slot])->isFree;
}

int Link::get_Availability() {
    int FreeSlots = 0;

    for (auto &slot : Slots) {
        if (slot->isFree) {
            FreeSlots++;
        }
    }

    return FreeSlots;
}

int Link::get_Occupability() {
    return Link::NumSlots - get_Availability();
}

int Link::get_Contiguity(std::shared_ptr<Call> C) {
    BOOST_ASSERT_MSG(C->Scheme.get_M() != 0,
                     "Can't calculate contiguity without knowing the modulation"
                     " scheme. Either you forgot to set it or one of the chosen "
                     "algorithms is not compatible with the contiguity measure");
    int NumRequiredSlots = C->Scheme.get_NumSlots(C->Bitrate);
    int Contiguity = 0;
    int CurrentFreeSlots = 0;
    bool SlotsAvailability[Link::NumSlots];

    for (int i = 0; i < Link::NumSlots; i++) {
        SlotsAvailability[i] = Slots[i]->isFree;
    }

    for (int sf = 0; sf < Link::NumSlots; sf++) {
        if (SlotsAvailability[sf]) {
            CurrentFreeSlots++;
        } else {
            CurrentFreeSlots = 0;
        }

        if (CurrentFreeSlots >= NumRequiredSlots) {
            Contiguity++;
        }
    }

    return Contiguity;
}

void Link::load() {
    std::cout << std::endl << "-> Define the distance between inline amplifiers."
              << std::endl;

    do {
        double SpanLeng;
        std::cin >> SpanLeng;

        if (std::cin.fail() || SpanLeng < 1) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid length." << std::endl;
            std::cout << std::endl << "-> Define the distance between inline amplifiers."
                      << std::endl;
        } else {
            AvgSpanLength = SpanLeng;
            break;
        }
    } while (1);
}
