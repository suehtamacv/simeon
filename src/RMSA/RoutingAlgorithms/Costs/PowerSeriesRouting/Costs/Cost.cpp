#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs/Cost.h>
#include <RMSA/RoutingAlgorithms/Costs/PowerSeriesRouting/Costs.h>
#include <boost/assign.hpp>
#include <Structure/Link.h>
#include <Calls/Call.h>

using namespace RMSA::ROUT::PSR;

Cost::CostNameBimap Cost::CostsNames =
    boost::assign::list_of<Cost::CostNameBimap::relation>
#define X(a,b,c,d) (a,b)
    POSSIBLECOSTS
#undef X
    ;

Cost::CostNicknameBimap Cost::CostsNicknames =
    boost::assign::list_of<Cost::CostNicknameBimap::relation>
#define X(a,b,c,d) (a,c)
    POSSIBLECOSTS
#undef X
    ;

Cost::Cost(int NMin, int NMax, std::shared_ptr<Topology> T,
           PossibleCosts Type) : Type(Type), NMin(NMin), NMax(NMax), T(T)
{

}

std::shared_ptr<Cost> Cost::createCost(PossibleCosts cost, int NMin, int NMax,
                                       std::shared_ptr<Topology> T)
{
    std::shared_ptr<Cost> Cost;

    switch (cost)
        {
#define X(a,b,c,d) case a: Cost = std::make_shared<d>(NMin, NMax, T);  break;
            POSSIBLECOSTS
#undef X
        }

    return Cost;
}

int Cost::get_NMin()
{
    return NMin;
}

int Cost::get_NMax()
{
    return NMax;
}

int Cost::get_N()
{
    return NMax - NMin + 1;
}

double Cost::getCost(int N, std::weak_ptr<Link> link, std::shared_ptr<Call> C)
{
    BOOST_ASSERT_MSG((N <= NMax) && (N >= NMin), "Invalid N requested");
    return getCost(link, C)(N - NMin);
}
