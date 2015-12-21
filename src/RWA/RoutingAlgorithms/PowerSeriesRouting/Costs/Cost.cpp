#include <RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost.h>
#include <boost/assign.hpp>
#include <Structure/Link.h>
#include <Calls/Call.h>

PSR::Cost::CostNameBimap PSR::Cost::CostsNames =
    boost::assign::list_of<PSR::Cost::CostNameBimap::relation>
#define X(a,b,c) (a,b)
    POSSIBLECOSTS
#undef X
    ;

PSR::Cost::CostNicknameBimap PSR::Cost::CostsNicknames =
    boost::assign::list_of<PSR::Cost::CostNicknameBimap::relation>
#define X(a,b,c) (a,c)
    POSSIBLECOSTS
#undef X
#undef POSSIBLECOSTS
    ;

PSR::Cost::Cost(int NMin, int NMax, std::shared_ptr<Topology> T) :
    NMin(NMin), NMax(NMax), T(T) {

}
