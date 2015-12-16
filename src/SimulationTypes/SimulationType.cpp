#include <SimulationTypes/SimulationType.h>
#include <boost/assign.hpp>
#include <iostream>

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
    std::cout << "\t* * * SIMULATOR OF SLICE OPTICAL NETWORKS * * *"
              << std::endl;

    std::cout << std::endl << "Choose a network type." << std::endl;

    do {
        for (auto nettype : NetworkTypes.left) {
            std::cout << "(" << nettype.first << ")\t" << nettype.second << std::endl;
        }

        int Net_Type;
        std::cin >> Net_Type;

        if (NetworkTypes.left.count((NetworkType) Net_Type) == 0) {
            std::cerr << "Invalid Network Type." << std::endl << std::endl;
        } else {
            Type = (NetworkType) Net_Type;
            break;
        }
    } while (1);

    std::cout << std::endl << "Choose a topology." << std::endl;

    do {
        for (auto topol : Topology::DefaultTopologiesNames.left) {
            std::cout << "(" << topol.first << ")\t" << topol.second << std::endl;
        }

        int Topol;
        std::cin >> Topol;

        if (Topology::DefaultTopologiesNames.left.count(
                    (Topology::DefaultTopologies) Topol) == 0) {
            std::cerr << "Invalid Topology." << std::endl << std::endl;
        } else {
            T = Topology(Topology::DefaultTopologiesPaths.left.at
                         ((Topology::DefaultTopologies) Topol));
            break;
        }
    } while (1);
}
