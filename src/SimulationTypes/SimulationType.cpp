#include <SimulationTypes/SimulationType.h>
#include <iostream>

SimulationType::NetworkTypeBimap SimulationType::NetworkTypes;

SimulationType::SimulationType() {
#define X(a,b) NetworkTypes.insert(NetworkTypeBimap::value_type(a,b));
    NETWORK_TYPE
#undef X
#undef NETWORK_TYPE
}

void SimulationType::load() {
    std::cout << "\t* * SIMULATOR OF SLICE OPTICAL NETWORKS * *"
              << std::endl << std::endl;

    std::cout << "Choose a network type." << std::endl;

    for (auto nettype : NetworkTypes.left) {
        std::cout << "(" << nettype.first << ")\t" << nettype.second << std::endl;
    }

    int Net_Type;
    std::cin >> Net_Type;
    Type = (NetworkType) Net_Type;
}
