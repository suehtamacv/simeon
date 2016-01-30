#ifndef ROUTINGALGORITHM_H
#define ROUTINGALGORITHM_H

#include <boost/bimap.hpp>
#include <memory>
#include <vector>

class Topology;
class Call;
class Link;

/**
 * @brief The RoutingAlgorithm class searches for a route, given a Call.
 */
class RoutingAlgorithm
{
public:
#define ROUTING_ALGORITHM \
    X(LORa, "Length and Occupation Routing - Availability", "LORa", LengthOccupationRoutingAvailability) \
    X(LORc, "Length and Occupation Routing - Contiguity", "LORc", LengthOccupationRoutingContiguity) \
    X(PSR, "Power Series Routing", "PSR", PowerSeriesRouting) \
    X(MH, "Minimum Hops", "MH", MinimumHops) \
    X(SP, "Shortest Path", "SP", ShortestPath) //Enum value, Name, Nickname, Class name.

#define X(a,b,c,d) a,
    enum RoutingAlgorithms
    {
        ROUTING_ALGORITHM
    };
#undef X

    typedef boost::bimap<RoutingAlgorithms, std::string> RoutAlgNameBimap;
    static RoutAlgNameBimap RoutingAlgorithmNames;
    typedef boost::bimap<RoutingAlgorithms, std::string> RoutAlgNicknameBimap;
    static RoutAlgNicknameBimap RoutingAlgorithmNicknames;

    RoutingAlgorithms RoutAlgType;

    RoutingAlgorithm(std::shared_ptr<Topology> T, RoutingAlgorithms RoutAlgType);

    static RoutingAlgorithms define_RoutingAlgorithm();
    static std::shared_ptr<RoutingAlgorithm> create_RoutingAlgorithm(
        RoutingAlgorithms, std::shared_ptr<Topology>);
    virtual std::vector<std::weak_ptr<Link>> route(std::shared_ptr<Call> C) = 0;
    virtual void load() = 0;
    virtual void save(std::string) = 0;

    std::shared_ptr<Topology> T;
};

#endif // ROUTINGALGORITHM_H
