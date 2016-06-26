#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RMSA/RoutingAlgorithms/RoutingCost.h>
#include <boost/assign.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <RMSA/RoutingAlgorithms.h>
#include <Structure.h>
#include <Calls/Call.h>

using namespace RMSA::ROUT;

RoutingAlgorithm::RoutTypeNameBimap RoutingAlgorithm::RoutingAlgorithmNames =
    boost::assign::list_of<RoutingAlgorithm::RoutTypeNameBimap::relation>
#define X(a,b,c,d) (a,b)
    ROUTING_ALGORITHM
#undef X
    ;

RoutingAlgorithm::RoutTypeNicknameBimap
RoutingAlgorithm::RoutingAlgorithmNicknames
    = boost::assign::list_of<RoutingAlgorithm::RoutTypeNicknameBimap::relation>
#define X(a,b,c,d) (a,c)
      ROUTING_ALGORITHM
#undef X
      ;

RoutingAlgorithm::RoutingAlgorithm(std::shared_ptr<Topology> T,
                                   RoutingAlgorithms RoutAlg,
                                   RoutingCost::RoutingCosts RoutCost,
                                   bool runLoad) :
    RoutAlg(RoutAlg), T(T)
{
    Cost = RoutCost;
    RCost = RoutingCost::create_RoutingCost(Cost, T, runLoad);
}

void RoutingAlgorithm::save(std::string SimConfigFileName)
{
    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

#ifdef RUN_ASSERTIONS
    EXPECT_TRUE(SimConfigFile.is_open()) << "Output file is not open";
#endif

    SimConfigFile << std::endl << "  [algorithms]" << std::endl << std::endl;
    SimConfigFile << "  RoutingAlgorithm = " <<
                  RoutingAlgorithmNicknames.left.at(RoutAlg) << std::endl;
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

}

RoutingAlgorithm::RoutingAlgorithms RoutingAlgorithm::define_RoutingAlgorithm()
{
    std::cout << std::endl << "-> Choose a routing algorithm." << std::endl;

    do
        {
        for (auto &routing : RoutingAlgorithmNames.left)
            {
            std::cout << "(" << routing.first << ")\t" << routing.second << std::endl;
            }

        int Routing_Alg;
        std::cin >> Routing_Alg;

        if (std::cin.fail() || RoutingAlgorithmNames.left.count
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
    RoutingAlgorithms Alg, RoutingCost::RoutingCosts Cost,
    std::shared_ptr<Topology> Top, bool runLoad)
{
    std::shared_ptr<RoutingAlgorithm> R_Alg;

    switch (Alg)
        {
#define X(a,b,c,d) case a: R_Alg = std::make_shared<d>(Top, Cost, runLoad); break;
            ROUTING_ALGORITHM
#undef X
        }

    if (runLoad)
        {
        R_Alg->load();
        }
    return R_Alg;
}

void RoutingAlgorithm::print()
{
    std::cout << "-> Routing Algorithm = " << RoutingAlgorithmNames.left.at(
                  RoutAlg) << std::endl;
}
