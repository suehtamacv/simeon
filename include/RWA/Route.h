#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <map>
#include <memory>
#include <RWA/TransparentSegment.h>

class Route {
  public:
    Route(std::vector<TransparentSegment> Segments,
          std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
          std::owner_less<std::weak_ptr<Link>>> Slots);
    Route(const Route &route);

    std::map<std::weak_ptr<Node>, unsigned int,
        std::owner_less<std::weak_ptr<Node>>> Regenerators;

    std::vector<TransparentSegment> Segments;
    std::vector<std::weak_ptr<Node>> Nodes;
    std::vector<std::weak_ptr<Link>> Links;
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;

    Signal bypass(Signal S);
    Signal &partial_bypass(Signal &S,
                           std::weak_ptr<Node> orig,
                           std::weak_ptr<Node> dest);
};

#endif // ROUTE_H
