#ifndef LINK_H
#define LINK_H

#include <Devices/Device.h>
#include <GeneralClasses/Signal.h>
#include <memory>
#include <vector>
#include <iostream>
#include <Structure/Slot.h>

class Node;
class Call;

class Link {
  public:
    static int NumSlots;
    static double AvgSpanLength;

    Link(std::weak_ptr<Node> Origin, std::weak_ptr<Node> Destination,
         double Length);
    Link(const Link &link);

    std::weak_ptr<Node> Origin;
    std::weak_ptr<Node> Destination;
    std::vector<std::shared_ptr<Slot>> Slots;
    std::vector<std::shared_ptr<Device>> Devices;

    double Length;
    int numLineAmplifiers;

    bool operator==(const Link &) const;
    bool operator<(const Link &) const;
    bool isSlotFree(int) const;

    Signal &bypass(Signal &);

    double get_Availability();
    double get_Occupability();
    double get_Contiguity(std::shared_ptr<Call> C);

    static void load();
  private:
    void create_Slots();
    void create_Devices();
};

#endif // LINK_H
