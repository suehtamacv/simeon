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

bool considerAseNoise = true;
bool considerFilterImperfection = false;

int main(void)
{
    std::cout << "\t* * * SIMULATOR OF SLICE OPTICAL NETWORKS * * *"
              << std::endl;

    auto simulation = Simulations::SimulationType::create();
    simulation->print();
    simulation->run();

    GaussianTransferFunction Teste(193.4e12 - 25e9, 193.4e12 + 25e9, 1000, 1);

    return 0;
}
