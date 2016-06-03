#ifndef FFE_GENERATION_H
#define FFE_GENERATION_H

#include "include/GeneralPurposeAlgorithms/GA/GA_Generation.h"

namespace RMSA
{
namespace SA
{
namespace FFE
{
class FFE_GA;

class FFE_Generation : public GeneticAlgorithm::GA_Generation
{
public:
    FFE_Generation(FFE_GA *GA);
    FFE_GA *GA;

    void breed(unsigned int a, unsigned int b, std::shared_ptr<GA_Generation> dest);
};
}
}
}

#endif // FFE_GENERATION_H
