#ifndef LENGTHOCCUPATIONROUTINGAVAILABILITY_H
#define LENGTHOCCUPATIONROUTINGAVAILABILITY_H

#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>

namespace RMSA
{
namespace ROUT
{
/**
 * @brief The LengthOccupationRoutingAvailability class represents the Length and
 * Occupation Routing algorithm (availability variant). Its link cost is a
 * ponderation with the link length and its availability.
 */
class LengthOccupationRoutingAvailability : public RoutingAlgorithm
{
public:
    LengthOccupationRoutingAvailability(std::shared_ptr<Topology> T);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);
    void load() {}
    void save(std::string);
};
}
}

#endif // LENGTHOCCUPATIONROUTINGAVAILABILITY_H
