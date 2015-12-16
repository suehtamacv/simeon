#ifndef ROUTINGALGORITHM_H
#define ROUTINGALGORITHM_H

#include <boost/bimap.hpp>
#include <memory>
#include <vector>
#include <Calls/Call.h>
#include <Structure/Topology.h>

/**
 * @brief The RoutingAlgorithm class searches for a route, given a Call.
 */
class RoutingAlgorithm {
  public:
#define ROUTING_ALGORITHM \
    X(LORa, "Length and Occupation Routing - Availability", "LORa") \
    X(LORc, "Length and Occupation Routing - Contiguity", "LORc") \
    X(MH, "Minimum Hops", "MH") \
    X(SP, "Shortest Path", "SP")

#define X(a,b,c) a,
    enum RoutingAlgorithms {
        ROUTING_ALGORITHM
    };
#undef X

    typedef boost::bimap<RoutingAlgorithms, std::string> RoutAlgNameBimap;
    static RoutAlgNameBimap RoutingAlgorithmNames;
    typedef boost::bimap<RoutingAlgorithms, std::string> RoutAlgNicknameBimap;
    static RoutAlgNicknameBimap RoutingAlgorithmNicknames;

    RoutingAlgorithm(std::shared_ptr<Topology> T);

    virtual std::vector<std::weak_ptr<Link>> route(std::shared_ptr<Call> C) = 0;

    std::shared_ptr<Topology> T;
};

#endif // ROUTINGALGORITHM_H
