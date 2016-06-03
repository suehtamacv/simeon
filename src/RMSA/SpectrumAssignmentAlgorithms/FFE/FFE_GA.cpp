#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_GA.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Generation.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Individual.h"
#include "include/SimulationTypes/Simulation_FFE_Optimization.h"
#include "include/Structure/Link.h"

using namespace RMSA::SA::FFE;
using namespace GeneticAlgorithm;

FFE_GA::FFE_GA(Simulations::Simulation_FFE_Optimization &Sim) : GA(), Sim(Sim)
{

}

void FFE_GA::createInitialGeneration()
{
    auto initialEvol = std::make_shared<FFE_Generation>(this);

    for (unsigned i = 0; i < numIndiv; ++i)
        {
        initialEvol->people.push_back(std::make_shared<FFE_Individual>
                                      (initialEvol.get()));
        }

    evolution.push_back(initialEvol);
}

std::shared_ptr<GA_Generation> FFE_GA::createEmptyGeneration()
{
    return std::make_shared<FFE_Generation>(this);
}
