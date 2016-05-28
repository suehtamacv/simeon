#ifndef FFE_GA_H
#define FFE_GA_H

#include "include/GeneralPurposeAlgorithms/GA/GA.h"

class Topology;

namespace Simulations
{
class Simulation_FFE_Optimization;
}

namespace RMSA
{
namespace SA
{
namespace FFE
{

class FFE_Generation;
class FFE_Individual;

class FFE_GA : public GeneticAlgorithm::GA
{
    friend class FFE_Generation;
    friend class FFE_Individual;

public:
    FFE_GA(Simulations::Simulation_FFE_Optimization &Sim);
    void createInitialGeneration();

private:
    Simulations::Simulation_FFE_Optimization &Sim;
};
}
}
}

#endif // FFE_GA_H
