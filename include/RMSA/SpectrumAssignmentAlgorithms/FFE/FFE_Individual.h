#ifndef FFE_INDIVIDUAL_H
#define FFE_INDIVIDUAL_H

#include "include/GeneralPurposeAlgorithms/GA/GA_Individual.h"

namespace RMSA
{
namespace SA
{
namespace FFE
{

class FFE_Generation;

class FFE_Individual : public GeneticAlgorithm::GA_Individual
{
public:
    FFE_Individual(FFE_Generation *G);

    void createIndividual();
    int createGene(unsigned int g);
    std::shared_ptr<GA_Individual> clone();
    void eval();
    GA_Individual& mutate();

private:
    FFE_Generation *G;
};
}
}
}

#endif // FFE_INDIVIDUAL_H
