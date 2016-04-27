#ifndef ROUTINGCOST_H
#define ROUTINGCOST_H

#include <memory>
#include <boost/bimap.hpp>

class Link;
class Topology;
class Call;

namespace RMSA
{
namespace ROUT
{
class RoutingCost
{
#define ROUTING_COSTS \
    X(AWR, "Adaptative Weighing Routing", "AWR", PSR::AdaptativeWeighingRouting) \
    X(LORa, "Length and Occupation Routing - Availability", "LORa", LengthOccupationRoutingAvailability) \
    X(LORc, "Length and Occupation Routing - Contiguity", "LORc", LengthOccupationRoutingContiguity) \
    X(localPSR, "Local Power Series Routing", "localPSR", PSR::LocalPowerSeriesRouting) \
    X(matPSR, "Matricial Power Series Routing", "matPSR", PSR::MatricialPowerSeriesRouting) \
    X(tenPSR, "Tensorial Power Series Routing", "tenPSR", PSR::TensorialPowerSeriesRouting) \
    X(MH, "Minimum Hops", "MH", MinimumHops) \
    X(SP, "Shortest Path", "SP", ShortestPath) //Enum value, Name, Nickname, Class name.

public:
#define X(a,b,c,d) a,
    enum RoutingCosts
    {
        ROUTING_COSTS
    };
#undef X

    RoutingCost(std::shared_ptr<Topology> T, RoutingCosts RoutCost);
    virtual double get_Cost(std::weak_ptr<Link> link, std::shared_ptr<Call> C) = 0;

    virtual void load() = 0;
    virtual void save(std::string) = 0;

    typedef boost::bimap<RoutingCosts, std::string> RoutAlgNameBimap;
    static RoutAlgNameBimap RoutingCostsNames;
    typedef boost::bimap<RoutingCosts, std::string> RoutAlgNicknameBimap;
    static RoutAlgNicknameBimap RoutingCostsNicknames;

    static RoutingCosts define_RoutingCost();
    static std::shared_ptr<RoutingCost> create_RoutingCost(RoutingCosts,
            std::shared_ptr<Topology>);

protected:
    std::shared_ptr<Topology> T;
    RoutingCosts RoutCost;
};
}
}

#endif // ROUTINGCOST_H
