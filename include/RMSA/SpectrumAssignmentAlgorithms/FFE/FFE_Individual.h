#ifndef FFE_INDIVIDUAL_H
#define FFE_INDIVIDUAL_H

#include "include/GeneralPurposeAlgorithms/GA/GA_Individual.h"

namespace RMSA
{
namespace SA
{
namespace FFE
{
class FFE_Individual : public GeneticAlgorithm::GA_Individual
{
public:
    FFE_Individual();

    void createIndividual();
    int createGene(unsigned int g);
    std::shared_ptr<GA_Individual> clone();
    void eval();
};
}
}
}

#endif // FFE_INDIVIDUAL_H
