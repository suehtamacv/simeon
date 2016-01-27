#ifndef LENGTHOCCUPATIONROUTINGCONTIGUITY_H
#define LENGTHOCCUPATIONROUTINGCONTIGUITY_H

#include <RWA/RoutingAlgorithms/DijkstraRoutingAlgorithm.h>

class LengthOccupationRoutingContiguity : public DijkstraRoutingAlgorithm
{
public:
    LengthOccupationRoutingContiguity(std::shared_ptr<Topology> T);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);
    void load() {}
    void save(std::string);
};

#endif // LENGTHOCCUPATIONROUTINGCONTIGUITY_H
