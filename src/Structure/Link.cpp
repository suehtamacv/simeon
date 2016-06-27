#include <cmath>
#include <iostream>
#include <Calls/Call.h>
#include <Structure/Link.h>
#include <Structure/Topology.h>
#include <Structure/Slot.h>
#include <Devices/Fiber.h>
#include <Devices/Amplifiers/InLineAmplifier.h>
#include <Devices/Amplifiers/PreAmplifier.h>

using namespace Devices;

int Link::NumSlots = 64;
double Link::DefaultAvgSpanLength = -1;

Link::Link(std::weak_ptr<Node> Origin,
           std::weak_ptr<Node> Destination,
           double Length)
{
#ifdef RUN_ASSERTIONS
    if (Length < 0)
        {
        std::cerr << "Length can't be negative." << std::endl;
        abort();
        }
#endif
    this->Origin = Origin;
    this->Destination = Destination;
    this->Length = Length;
    isActive = true;
    AvgSpanLength = DefaultAvgSpanLength;

    create_Slots();
    create_Devices();

    linkSpecDens = std::make_shared<LinkSpectralDensity>(Slots);
}

Link::Link(const Link &link) // linkSpecDens aqui?
{
    Length = link.Length;
    Origin = link.Origin;
    Destination = link.Destination;
    AvgSpanLength = link.AvgSpanLength;
    isActive = link.isActive;

    for (auto &slot : link.Slots)
        {
        Slots.push_back(std::shared_ptr<Slot>(new Slot(*slot)));
        }

    for (auto &device : link.Devices)
        {
        Devices.push_back(device->clone());
        }
}

void Link::create_Slots()
{
    for (int i = 0; i < NumSlots; i++)
        {
        Slots.push_back(std::shared_ptr<Slot>(new Slot(i)));
        }
}

void Link::create_Devices()
{
    if (AvgSpanLength < 0)
        {
        return;
        }

    Devices.clear();
    numLineAmplifiers = floor(Length / AvgSpanLength);

    if (ceil(Length / AvgSpanLength) == numLineAmplifiers)
        {
        numLineAmplifiers--;
        }

    double SpanLength = Length / (numLineAmplifiers + 1);

    for (int i = 0; i < numLineAmplifiers; i++)
        {
        Devices.push_back(std::make_shared<Fiber>(SpanLength));
        Devices.push_back(std::make_shared<InLineAmplifier>((Fiber &)*Devices.back()));
        }

    //There's an extra fiber segment in the end of the link
    Devices.push_back(std::make_shared<Fiber>(SpanLength));

    //There's a preamplifier in the node's entrance.
    //It compensates the fiber segment loss and also the switching element loss.
    Devices.push_back(std::make_shared<PreAmplifier>((Fiber &)*Devices.back(), *Destination.lock()));
}

bool Link::operator ==(const Link &link) const
{
    return (Length == link.Length) &&
           (*(Origin.lock()) == *(link.Origin.lock())) &&
           (*(Destination.lock()) == *(link.Destination.lock()));
}

bool Link::operator !=(const Link &link) const
{
    return !(operator ==(link));
}

Signal &Link::bypass(Signal &S)
{
    for (auto &link : Origin.lock()->Links)
        {
        if (*link == *this)
            {
            S.incomingLink = link;
            break;
            }
        }

    for (auto &it : Devices)
        {
        S *= it->get_Gain();
        S += it->get_Noise();
        if (considerFilterImperfection)
            {
            S *= it->get_TransferFunction((S.freqMin + S.freqMax) / 2.0); //central frequency
            }
        }

    return S;
}

bool Link::isSlotFree(int slot) const
{
#ifdef RUN_ASSERTIONS
    if (slot >= NumSlots)
        {
        std::cerr << "Invalid slot requested." << std::endl;
        abort();
        }
#endif
    return (Slots[slot])->isFree;
}

int Link::get_Availability()
{
    int FreeSlots = 0;

    for (auto &slot : Slots)
        {
        if (slot->isFree)
            {
            FreeSlots++;
            }
        }

    return FreeSlots;
}

int Link::get_Occupability()
{
    return Link::NumSlots - get_Availability();
}

int Link::get_Contiguity(std::shared_ptr<Call> C)
{
#ifdef RUN_ASSERTIONS
    if (C->Scheme.get_M() == 0)
        {
        std::cerr << "Can't calculate contiguity without knowing the modulation"
                  " scheme. Either you forgot to set it or one of the chosen "
                  "algorithms is not compatible with the contiguity measure" << std::endl;
        abort();
        }
#endif
    int NumRequiredSlots = C->Scheme.get_NumSlots(C->Bitrate);
    int Contiguity = 0;
    int CurrentFreeSlots = 0;

    for (int s = 0; s < Link::NumSlots; s++)
        {
        if (Slots[s]->isFree)
            {
            CurrentFreeSlots++;
            }
        else
            {
            CurrentFreeSlots = 0;
            }

        if (CurrentFreeSlots >= NumRequiredSlots)
            {
            Contiguity++;
            }
        }

    return Contiguity;
}

void Link::load(std::shared_ptr<Topology> T)
{
    std::cout << std::endl << "-> Define the distance between inline amplifiers."
              << std::endl;

    do
        {
        double SpanLeng;
        std::cin >> SpanLeng;

        if (std::cin.fail() || SpanLeng < 1)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid length." << std::endl;
            std::cout << std::endl << "-> Define the distance between inline amplifiers."
                      << std::endl;
            }
        else
            {
            DefaultAvgSpanLength = SpanLeng;
            break;
            }
        }
    while (1);

    T->set_avgSpanLength(DefaultAvgSpanLength);
}

void Link::save(std::string SimConfigFileName, std::shared_ptr<Topology> T)
{
    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

#ifdef RUN_ASSERTIONS
    if (!SimConfigFile.is_open())
        {
        std::cerr << "Output file is not open" << std::endl;
        abort();
        }
#endif

    SimConfigFile << "  AvgSpanLength = " << T->AvgSpanLength << std::endl;
}

double Link::get_CapEx()
{
    double CapEx = 0;

    for (auto device : Devices)
        {
        CapEx += device->get_CapEx();
        }

    return CapEx;
}

double Link::get_OpEx()
{
    double OpEx = 0;

    for (auto device : Devices)
        {
        OpEx += device->get_OpEx();
        }

    return OpEx;
}

void Link::set_AvgSpanLength(double avgSpanLength)
{
    AvgSpanLength = avgSpanLength;
    create_Devices();
}

void Link::set_LinkActive()
{
    isActive = true;
}

void Link::set_LinkInactive()
{
    isActive = false;
}

std::ostream& operator <<(std::ostream &out, const Link &link)
{
    return out << "Link: (" << *(link.Origin.lock()) << " -> " << *
           (link.Destination.lock()) << "), length = " << link.Length << "km";
}
