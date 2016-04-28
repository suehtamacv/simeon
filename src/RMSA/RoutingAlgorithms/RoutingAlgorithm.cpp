#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RMSA/RoutingAlgorithms/RoutingCost.h>
#include <boost/assign.hpp>
#include <iostream>
#include <fstream>
#include <RMSA/RoutingAlgorithms.h>
#include <Structure.h>
#include <Calls/Call.h>

using namespace RMSA::ROUT;

bool RoutingAlgorithm::hasLoadedRoutingCost = false;
RoutingCost::RoutingCosts RoutingAlgorithm::Cost;

RoutingAlgorithm::RoutTypeNameBimap RoutingAlgorithm::RoutAlgorithmNames =
    boost::assign::list_of<RoutingAlgorithm::RoutTypeNameBimap::relation>
#define X(a,b,c,d) (a,b)
    ROUTING_ALGORITHM
#undef X
    ;

RoutingAlgorithm::RoutTypeNicknameBimap
RoutingAlgorithm::RoutAlgorithmNicknames
    = boost::assign::list_of<RoutingAlgorithm::RoutTypeNicknameBimap::relation>
#define X(a,b,c,d) (a,c)
      ROUTING_ALGORITHM
#undef X
      ;

RoutingAlgorithm::RoutingAlgorithm(std::shared_ptr<Topology> T,
                                   RoutingAlgorithms RoutAlg) :
    RoutAlg(RoutAlg), T(T)
{
    if (hasLoadedRoutingCost)
        {
        RCost = RoutingCost::create_RoutingCost(Cost, T);
        }
}

RoutingAlgorithm::RoutingAlgorithm(std::shared_ptr<Topology> T,
                                   RoutingAlgorithms RoutAlg, RoutingCost::RoutingCosts RoutCost) :
    RoutingAlgorithm(T, RoutAlg)
{
    Cost = RoutCost;
    RCost = RoutingCost::create_RoutingCost(Cost, T);
    hasLoadedRoutingCost = true;
}

void RoutingAlgorithm::save(std::string SimConfigFileName)
{
    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << std::endl << "  [algorithms]" << std::endl << std::endl;
    SimConfigFile << "  RoutingAlgorithm = " << RoutAlgorithmNicknames.left.at(
                      RoutAlg)
                  << std::endl;
}

double RoutingAlgorithm::get_RoutingCost(std::vector<std::weak_ptr<Link>> links,
        std::shared_ptr<Call> C)
{
    double cost = 0;

    for (auto &link : links)
        {
        cost += RCost->get_Cost(link, C);
        }

    return cost;
}

void RoutingAlgorithm::load()
{
    if (hasLoadedRoutingAlg)
        {
        return;
        }

    std::cout << std::endl << "-> Choose a routing algorithm." << std::endl;

    do
        {
        for (auto &routing : RoutAlgorithmNames.left)
            {
            std::cout << "(" << routing.first << ")\t" << routing.second << std::endl;
            }

        int Routing_Alg;
        std::cin >> Routing_Alg;

        if (std::cin.fail() || RoutAlgorithmNames.left.count
                ((RoutingAlgorithms) Routing_Alg) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid routing type." << std::endl;
            std::cout << std::endl << "-> Choose a routing algorithm." << std::endl;
            }
        else
            {
            RoutAlg = (RoutingAlgorithms) Routing_Alg;
            break;
            }
        }
    while (1);

    auto Routing_Cost = RoutingCost::define_RoutingCost();
    RCost = RoutingCost::create_RoutingCost(Routing_Cost, T);

    hasLoadedRoutingCost = true;
}

RoutingAlgorithm::RoutingAlgorithms RoutingAlgorithm::define_RoutingAlgorithm()
{
    std::cout << std::endl << "-> Choose a routing algorithm." << std::endl;

    do
        {
        for (auto &routing : RoutAlgorithmNames.left)
            {
            std::cout << "(" << routing.first << ")\t" << routing.second << std::endl;
            }

        int Routing_Alg;
        std::cin >> Routing_Alg;

        if (std::cin.fail() || RoutAlgorithmNames.left.count
                ((RoutingAlgorithms) Routing_Alg) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid routing algorithm." << std::endl;
            std::cout << std::endl << "-> Choose a routing algorithm." << std::endl;
            }
        else
            {
            return (RoutingAlgorithms) Routing_Alg;
            }
        }
    while (1);

    return (RoutingAlgorithms) - 1;
}

std::shared_ptr<RoutingAlgorithm> RoutingAlgorithm::create_RoutingAlgorithm(
    RoutingAlgorithms Alg, std::shared_ptr<Topology> T)
{
    std::shared_ptr<RoutingAlgorithm> R_Alg;

    switch (Alg)
        {
#define X(a,b,c,d) case a: R_Alg = std::make_shared<d>(T); break;
            ROUTING_ALGORITHM
#undef X
        }

    R_Alg->load();
    return R_Alg;
}
