#include <RWA/RoutingAlgorithms/PowerSeriesRouting/Costs/Cost.h>
#include <RWA/RoutingAlgorithms/PowerSeriesRouting/Costs.h>
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

PSR::Cost::Cost(int NMin, int NMax, std::shared_ptr<Topology> T,
                PossibleCosts Type) : Type(Type), NMin(NMin), NMax(NMax), T(T)
{

}

std::shared_ptr<PSR::Cost> PSR::Cost::createCost(PossibleCosts cost, int NMin,
        int NMax, std::shared_ptr<Topology> T)
{
    std::shared_ptr<PSR::Cost> Cost;

    switch (cost)
        {
        case availability:
            Cost = std::make_shared<PSR::cAvailability>(NMin, NMax, T);
            break;

        case bitrate:
            Cost = std::make_shared<PSR::cBitrate>(NMin, NMax, T);
            break;

        case contiguity:
            Cost = std::make_shared<PSR::cContiguity>(NMin, NMax, T);
            break;

        case distance:
            Cost = std::make_shared<PSR::cDistance>(NMin, NMax, T);
            break;

        case noise:
            Cost = std::make_shared<PSR::cNoise>(NMin, NMax, T);
            break;

        case normcontiguity:
            Cost = std::make_shared<PSR::cNormContiguity>(NMin, NMax, T);
            break;

        case normnoise:
            Cost = std::make_shared<PSR::cNormNoise>(NMin, NMax, T);
            break;

        case occupability:
            Cost = std::make_shared<PSR::cOccupability>(NMin, NMax, T);
            break;

        case scheme:
            Cost = std::make_shared<PSR::cModulationScheme>(NMin, NMax, T);
            break;

        case slots:
            Cost = std::make_shared<PSR::cSlots>(NMin, NMax, T);
            break;
        }

    return Cost;
}

int PSR::Cost::get_NMin()
{
    return NMin;
}

int PSR::Cost::get_NMax()
{
    return NMax;
}

int PSR::Cost::get_N()
{
    return NMax - NMin + 1;
}
