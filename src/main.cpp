#include "GeneralClasses.h"
#include "Devices.h"
#include "Structure.h"
#include "Calls.h"
#include "RWA.h"
#include "SimulationTypes.h"

#include <GeneralClasses/TransferFunctions/GaussianTransferFunction.h>

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

    auto simulation = Simulations::SimulationType::open(); // removi create
    simulation->print();
    simulation->run();

    return 0;
}
