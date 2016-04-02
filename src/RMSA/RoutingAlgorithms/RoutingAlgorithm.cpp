#include <RWA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <boost/assign.hpp>
#include <iostream>
#include <fstream>
#include <RWA/RoutingAlgorithms.h>

RoutingAlgorithm::RoutAlgNameBimap RoutingAlgorithm::RoutingAlgorithmNames =
    boost::assign::list_of<RoutingAlgorithm::RoutAlgNameBimap::relation>
#define X(a,b,c,d) (a,b)
    ROUTING_ALGORITHM
#undef X
    ;

RoutingAlgorithm::RoutAlgNicknameBimap
RoutingAlgorithm::RoutingAlgorithmNicknames =
    boost::assign::list_of<RoutingAlgorithm::RoutAlgNicknameBimap::relation>
#define X(a,b,c,d) (a,c)
    ROUTING_ALGORITHM
#undef X
    ;

RoutingAlgorithm::RoutingAlgorithm(std::shared_ptr<Topology> T,
                                   RoutingAlgorithms RoutAlgType) :
    RoutAlgType(RoutAlgType), T(T)
{

}

RoutingAlgorithm::RoutingAlgorithms
RoutingAlgorithm::define_RoutingAlgorithm()
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
    RoutingAlgorithms Algorithm, std::shared_ptr<Topology> T)
{
    std::shared_ptr<RoutingAlgorithm> R_Alg;

    switch (Algorithm)
        {
#define X(a,b,c,d) case a: R_Alg = std::make_shared<d>(T); break;
            ROUTING_ALGORITHM
#undef X
        }

    R_Alg->load();
    return R_Alg;
}

void RoutingAlgorithm::save(std::string SimConfigFileName)
{
    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << std::endl << "  [algorithms]" << std::endl << std::endl;
    SimConfigFile << "  RoutingAlgorithm = " << RoutingAlgorithmNicknames.left.at(
                      RoutAlgType)
                  << std::endl;
}
