#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Individual.h"
#include "include/Structure/Link.h"
#include "include/GeneralClasses/RandomGenerator.h"
#include <algorithm>

using namespace RMSA::SA::FFE;
using namespace GeneticAlgorithm;

FFE_Individual::FFE_Individual() : GA_Individual()
{
    createIndividual();
}

void FFE_Individual::createIndividual()
{
    Gene = std::vector<int>(Link::NumSlots);
    std::iota(Gene.begin(), Gene.end(), 0);
    std::random_shuffle(Gene.begin(), Gene.end());
}

int FFE_Individual::createGene(unsigned int g)
{
    std::uniform_int_distribution<unsigned int> Dist(0, Link::NumSlots - 1);
    unsigned int newGene;

    do
        {
        newGene = Dist(random_generator);
        }
    while (g == newGene);

    return newGene;
}

void FFE_Individual::eval()
{

}

std::shared_ptr<GA_Individual> FFE_Individual::clone()
{
    std::shared_ptr<FFE_Individual> individual = std::make_shared<FFE_Individual>();
    individual->Gene = Gene;
    individual->parameter = parameter;
    return individual;
}
