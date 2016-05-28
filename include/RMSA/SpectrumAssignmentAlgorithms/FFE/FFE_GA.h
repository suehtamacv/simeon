#ifndef FFE_GA_H
#define FFE_GA_H

#include "include/GeneralPurposeAlgorithms/GA/GA.h"

namespace RMSA
{
namespace SA
{
namespace FFE
{
class FFE_GA : public GeneticAlgorithm::GA
{
public:
    FFE_GA();
    void createInitialGeneration();
};
}
}
}

#endif // FFE_GA_H
