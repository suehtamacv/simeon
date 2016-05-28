#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_GA.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Generation.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Individual.h"
#include "include/Structure/Link.h"

using namespace RMSA::SA::FFE;
using namespace GeneticAlgorithm;

FFE_GA::FFE_GA() : GA()
{

}

void FFE_GA::createInitialGeneration()
{
    auto initialEvol = std::make_shared<FFE_Generation>();

    for (unsigned i = 0; i < numIndiv; ++i)
        {
        initialEvol->people.emplace(std::make_shared<FFE_Individual>());
        }

    evolution.push_back(initialEvol);
}
