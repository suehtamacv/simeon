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
        initialEvol->people.push_back(std::make_shared<FFE_Individual>(initialEvol.get()));
        }

    //Sets a individual with FF Genes.
    auto FirstFit_Gene = std::vector<int>(Link::NumSlots);
    std::iota(FirstFit_Gene.begin(), FirstFit_Gene.end(), 0);
    initialEvol->people[0]->setGene(FirstFit_Gene);

    evolution.push_back(initialEvol);
}
