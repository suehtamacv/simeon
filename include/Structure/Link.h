#ifndef LINK_H
#define LINK_H

#include <Devices/Device.h>
#include <Devices/Fiber.h>
#include <Devices/Amplifier.h>
#include <Structure/Slot.h>
#include <memory>
#include <vector>

class Node;

class Link {
  public:
	constexpr static int NumSlots = 64;
	static long double AvgSpanLength;

	Link(std::weak_ptr<Node> Origin, std::weak_ptr<Node> Destination, long double Length);

	std::weak_ptr<Node> Origin;
	std::weak_ptr<Node> Destination;
	long double Length;

  private:
	void create_Slots();
	void create_Devices();
	std::vector<std::unique_ptr<Slot>> Slots;
	std::vector<std::unique_ptr<Device>> Devices;
};

#endif // LINK_H
