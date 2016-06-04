#include "SimulationTypes.h"
#include <gtest/gtest.h>

namespace Simulations
{
bool parallelism_enabled = true;
}

bool considerAseNoise = false;
bool considerFilterImperfection = false;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
#ifdef IS_DEBUG
    return RUN_ALL_TESTS();
#endif

    std::cout << "\t* * * SIMULATOR OF SLICE OPTICAL NETWORKS * * *"
              << std::endl;

    auto simulation = Simulations::SimulationType::create();
    simulation->print();
    simulation->run();

    return 0;
}
