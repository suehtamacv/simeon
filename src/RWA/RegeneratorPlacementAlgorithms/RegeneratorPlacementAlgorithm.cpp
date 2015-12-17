#include <RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>
#include <RWA/RegeneratorPlacementAlgorithms.h>
#include <boost/assign.hpp>
#include <iostream>

RegeneratorPlacementAlgorithm::RegPlaceNameBimap
RegeneratorPlacementAlgorithm::RegeneratorPlacementNames =
    boost::assign::list_of<RegeneratorPlacementAlgorithm::RegPlaceNameBimap::relation>
#define X(a,b,c) (a,b)
    REGPLACEMENT_ALGORITHMS
#undef X
    ;

RegeneratorPlacementAlgorithm::RegPlaceNicknameBimap
RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames =
    boost::assign::list_of<RegeneratorPlacementAlgorithm::RegPlaceNicknameBimap::relation>
#define X(a,b,c) (a,c)
    REGPLACEMENT_ALGORITHMS
#undef X
#undef REGPLACEMENT_ALGORITHMS
    ;

RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithm(
    std::shared_ptr<Topology> T) : T(T) {

}

RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
RegeneratorPlacementAlgorithm::define_RegeneratorPlacementAlgorithm() {
    std::cout << std::endl << "-> Choose a regenerator placement algorithm."
              << std::endl;

    do {
        for (auto rplace : RegeneratorPlacementNames.left) {
            std::cout << "(" << rplace.first << ")\t" << rplace.second << std::endl;
        }

        int RegPlace_Alg;
        std::cin >> RegPlace_Alg;

        if (std::cin.fail() || RegeneratorPlacementNames.left.count
                ((RegeneratorPlacementAlgorithms) RegPlace_Alg) == 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid regenerator placement algorithm." << std::endl;
            std::cout << std::endl << "-> Choose a regenerator placement algorithm."
                      << std::endl;
        } else {
            return (RegeneratorPlacementAlgorithms) RegPlace_Alg;
        }
    } while (1);

    return (RegeneratorPlacementAlgorithms) - 1;
}

std::shared_ptr<RegeneratorPlacementAlgorithm>
RegeneratorPlacementAlgorithm::create_RegeneratorPlacementAlgorithm(
    RegeneratorPlacementAlgorithms Algorithm,
    std::shared_ptr<Topology> T) {
    std::shared_ptr<RegeneratorPlacementAlgorithm> RP_Alg;

    switch (Algorithm) {

    }
}
