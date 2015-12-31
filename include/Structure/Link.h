#ifndef LINK_H
#define LINK_H

#include <GeneralClasses/Signal.h>
#include <memory>
#include <vector>

class Node;
class Call;
class Slot;
class Device;

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

    int get_Availability();
    int get_Occupability();
    int get_Contiguity(std::shared_ptr<Call> C);

    static void load();
  private:
    void create_Slots();
    void create_Devices();
};

#endif // LINK_H
