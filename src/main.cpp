#include "SimulationTypes.h"

namespace Simulations
{
bool parallelism_enabled = true;
}

bool considerAseNoise = false;
bool considerFilterImperfection = false;

int main(void)
{
    std::cout << "\t* * * SIMULATOR OF SLICE OPTICAL NETWORKS * * *"
              << std::endl;

    auto simulation = Simulations::SimulationType::create(); // For regular simulations
    //auto simulation = Simulations::SimulationType::open(); // For testing Save/Load functions
    simulation->print();
    simulation->run();

    return 0;
}
