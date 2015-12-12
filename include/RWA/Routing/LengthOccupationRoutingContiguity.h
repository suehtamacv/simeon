#ifndef LENGTHOCCUPATIONROUTINGCONTIGUITY_H
#define LENGTHOCCUPATIONROUTINGCONTIGUITY_H

#include <RWA/Routing/DijkstraRoutingAlgorithm.h>

class LengthOccupationRoutingContiguity : public DijkstraRoutingAlgorithm {
  public:
    LengthOccupationRoutingContiguity(std::shared_ptr<Topology> T);
    long double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);
};

#endif // LENGTHOCCUPATIONROUTINGCONTIGUITY_H
