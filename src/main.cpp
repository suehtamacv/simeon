#include "GeneralClasses.h"
#include "Devices.h"
#include "Structure.h"
#include "Calls.h"
#include "RWA.h"
#include "SimulationTypes.h"

namespace Simulations
{
bool parallelism_enabled = true;
}

int main(void)
{
    std::cout << "\t* * * SIMULATOR OF SLICE OPTICAL NETWORKS * * *"
              << std::endl;

    auto simulation = Simulations::SimulationType::create();
    simulation->print();
    simulation->run();

    return 0;
}
