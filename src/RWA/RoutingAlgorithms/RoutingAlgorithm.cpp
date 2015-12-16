#include <RWA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <boost/assign.hpp>

RoutingAlgorithm::RoutAlgNameBimap RoutingAlgorithm::RoutingAlgorithmNames =
    boost::assign::list_of<RoutingAlgorithm::RoutAlgNameBimap::relation>
#define X(a,b,c) (a,b)
    ROUTING_ALGORITHM
#undef X
    ;

RoutingAlgorithm::RoutAlgNicknameBimap
RoutingAlgorithm::RoutingAlgorithmNicknames =
    boost::assign::list_of<RoutingAlgorithm::RoutAlgNicknameBimap::relation>
#define X(a,b,c) (a,c)
    ROUTING_ALGORITHM
#undef X
#undef ROUTING_ALGORITHM
    ;


RoutingAlgorithm::RoutingAlgorithm(std::shared_ptr<Topology> T) : T(T) {

}

