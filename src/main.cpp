#include "GeneralClasses.h"
#include "Devices.h"
#include "Structure.h"
#include "Calls.h"
#include "RWA.h"
#include "SimulationTypes.h"

#include <iostream>

int main(void) {
    std::cout << "\t* * * SIMULATOR OF SLICE OPTICAL NETWORKS * * *"
              << std::endl;

    ///Simulation_NetworkLoad simulation;
    ///simulation.print();

    Simulation_PSROptimization simulation2;
    simulation2.print();

    return 0;
}
