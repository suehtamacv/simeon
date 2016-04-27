#ifndef LENGTHOCCUPATIONROUTINGCONTIGUITY_H
#define LENGTHOCCUPATIONROUTINGCONTIGUITY_H

#include <RMSA/RoutingAlgorithms/RoutingCost.h>

namespace RMSA
{
namespace ROUT
{
/**
 * @brief The LengthOccupationRoutingContiguity class represents the Length and
 * Occupation Routing algorithm (contiguity variant). Its link cost is a
 * ponderation with the link length and its contiguity.
 */
class LengthOccupationRoutingContiguity : public RoutingCost
{
public:
    LengthOccupationRoutingContiguity(std::shared_ptr<Topology> T);

    double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

    void load()
    {
        RoutingCost::load();
    }
    void save(std::string);
};
}
}

#endif // LENGTHOCCUPATIONROUTINGCONTIGUITY_H
