#include "include/GeneralPurposeAlgorithms/GA/GA_Individual.h"
#include "include/GeneralClasses/RandomGenerator.h"
#include <iostream>

using namespace GeneticAlgorithm;

GA_Individual::GA_Individual()
{
    isEvaluated = false;
    parameter = -1;
}

bool GA_Individual::operator ==(const GA_Individual &other) const
{
    return (Gene == other.Gene);
}

bool GA_Individual::operator <(const GA_Individual &other) const
{
    return (parameter < other.parameter);
}

GA_Individual& GA_Individual::mutate()
{
    std::uniform_int_distribution<int> dist(0, Gene.size() - 1);

    for (unsigned gene = 0; gene < GA::mutationPoints; ++gene)
        {
        int g = dist(random_generator);
        std::swap(Gene[g], Gene[createGene(g)]);
        isEvaluated = false;
        }

    return *this;
}

void GA_Individual::setGene(std::vector<int> newGene)
{
    Gene = newGene;
    isEvaluated = false;
}

std::vector<int> GA_Individual::getGenes() const
{
    return Gene;
}

std::string GA_Individual::print(bool pretty)
{
    if (pretty)
        {
        std::cout << "Individual: " << parameter << std::endl;
        return "";
        }
    else
        {
        std::string indiv = "";

        for (auto &g : Gene)
            {
            indiv += std::to_string(g);
            indiv += " ";
            }

        return indiv;
        }
}

