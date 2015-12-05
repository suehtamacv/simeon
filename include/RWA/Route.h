#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <map>
#include <memory>

class Link;
class Node;
class Slot;

class Route {
  public:
    Route(std::vector<std::weak_ptr<Link>> Links,
          std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>> Slots);

    std::vector<std::weak_ptr<Node>> Nodes;
    std::vector<std::weak_ptr<Link>> Links;
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>> Slots;
};

#endif // ROUTE_H
