#include <SimulationTypes/SimulationType.h>
#include <boost/assign.hpp>
#include <iostream>

SimulationType::NetworkType SimulationType::Type;

SimulationType::NetworkTypeBimap SimulationType::NetworkTypes =
    boost::assign::list_of<SimulationType::NetworkTypeBimap::relation>
#define X(a,b) (a,b)
    NETWORK_TYPE
#undef X
#undef NETWORK_TYPE
    ;

SimulationType::SimulationType() {
}

void SimulationType::load() {
    std::cout << std::endl << "-> Choose a topology." << std::endl;

    do {
        for (auto topol : Topology::DefaultTopologiesNames.left) {
            std::cout << "(" << topol.first << ")\t" << topol.second << std::endl;
        }

        int Topol;
        std::cin >> Topol;

        if (std::cin.fail() || Topology::DefaultTopologiesNames.left.count(
                    (Topology::DefaultTopologies) Topol) == 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Topology." << std::endl;
            std::cout << std::endl << "-> Choose a topology." << std::endl;
        } else {
            Chosen_Topology = (Topology::DefaultTopologies) Topol;
            T = Topology::create_DefaultTopology(Chosen_Topology);
            break;
        }
    } while (1);

}
