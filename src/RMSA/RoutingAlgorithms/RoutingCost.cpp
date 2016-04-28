#include "include/RMSA/RoutingAlgorithms/RoutingCost.h"
#include "include/RMSA/RoutingCosts.h"
#include <boost/assign.hpp>
#include <iostream>

using namespace RMSA::ROUT;

RoutingCost::RoutAlgNameBimap RoutingCost::RoutingCostsNames =
    boost::assign::list_of<RoutingCost::RoutAlgNameBimap::relation>
#define X(a,b,c,d) (a,b)
    ROUTING_COSTS
#undef X
    ;

RoutingCost::RoutAlgNicknameBimap RoutingCost::RoutingCostsNicknames =
    boost::assign::list_of<RoutingCost::RoutAlgNicknameBimap::relation>
#define X(a,b,c,d) (a,c)
    ROUTING_COSTS
#undef X
    ;

RoutingCost::RoutingCost(std::shared_ptr<Topology> T,
                         RoutingCosts RoutCost) :
    T(T), RoutCost(RoutCost)
{

}

RoutingCost::RoutingCosts RoutingCost::define_RoutingCost()
{
    std::cout << std::endl << "-> Choose a routing cost." << std::endl;

    do
        {
        for (auto &routing : RoutingCostsNames.left)
            {
            std::cout << "(" << routing.first << ")\t" << routing.second << std::endl;
            }

        int Routing_Cost;
        std::cin >> Routing_Cost;

        if (std::cin.fail() || RoutingCostsNames.left.count
                ((RoutingCosts) Routing_Cost) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid routing cost." << std::endl;
            std::cout << std::endl << "-> Choose a routing cost." << std::endl;
            }
        else
            {
            return (RoutingCosts) Routing_Cost;
            }
        }
    while (1);

    return (RoutingCosts) - 1;
}

std::shared_ptr<RoutingCost> RoutingCost::create_RoutingCost(
    RoutingCosts Cost, std::shared_ptr<Topology> T)
{
    std::shared_ptr<RoutingCost> R_Cost;

    switch (Cost)
        {
#define X(a,b,c,d) case a: R_Cost = std::make_shared<d>(T); break;
            ROUTING_COSTS
#undef X
        }

    R_Cost->load();
    return R_Cost;
}
