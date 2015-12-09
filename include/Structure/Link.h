#ifndef LINK_H
#define LINK_H

#include <Devices/Device.h>
#include <GeneralClasses/Signal.h>
#include <memory>
#include <vector>
#include <Structure/Slot.h>

class Node;

class Link {
  public:
    constexpr static int NumSlots = 64;
    constexpr static long double AvgSpanLength = 80;

    Link(std::weak_ptr<Node> Origin, std::weak_ptr<Node> Destination,
         long double Length);

    std::weak_ptr<Node> Origin;
    std::weak_ptr<Node> Destination;
    std::vector<std::shared_ptr<Slot>> Slots;
    std::vector<std::shared_ptr<Device>> Devices;

    long double Length;
    int numLineAmplifiers;

    bool operator==(Link *) const;
    bool operator<(Link *) const;
    bool isSlotFree(unsigned int) const;

    Signal bypass(Signal);

  private:
    void create_Slots();
    void create_Devices();
};

#endif // LINK_H
