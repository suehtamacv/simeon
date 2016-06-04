#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Generation.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Individual.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_GA.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/SpectrumAssignmentAlgorithm.h"
#include "include/Structure/Link.h"
#include "include/GeneralClasses/RandomGenerator.h"

using namespace RMSA::SA::FFE;
using namespace GeneticAlgorithm;

FFE_Generation::FFE_Generation(FFE_GA *GA) : GA_Generation(), GA(GA)
{

}

void FFE_Generation::breed(unsigned int a, unsigned int b,
                           std::shared_ptr<GA_Generation> dest)
{
    if (a == b)
        {
        return;
        }

    auto iterator_a = people.begin();
    auto iterator_b = people.begin();
    std::advance(iterator_a, a);
    std::advance(iterator_b, b);

    std::map<int, std::vector<int>> GeneA = (*iterator_a)->getGenes(),
                                    GeneB = (*iterator_b)->getGenes();
    std::uniform_int_distribution<int> dist(1, GeneA.size() - 1);
    int crossOverPoint = dist(random_generator);

    for (size_t i = crossOverPoint; i < GeneA.size(); ++i)
        {
        auto nSlot = SpectrumAssignmentAlgorithm::possibleRequiredSlots.begin();
        std::advance(nSlot, i);
        std::swap(GeneA[*nSlot], GeneB[*nSlot]); //swaps genes of the individuals
        }

    auto newIndivA = (*iterator_a)->clone(), newIndivB = (*iterator_b)->clone();
    newIndivA->setGene(GeneA);
    newIndivB->setGene(GeneB);
    (*dest) += newIndivA;
    (*dest) += newIndivB;

    people.erase(iterator_a);
    people.erase(iterator_b);
}
