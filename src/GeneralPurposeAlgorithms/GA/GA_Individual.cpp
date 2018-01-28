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
    return (parameter == other.parameter);
}

bool GA_Individual::operator <(const GA_Individual &other) const
{
    return (parameter < other.parameter);
}

GA_Individual& GA_Individual::mutate()
{
    isEvaluated = false;
    return *this;
}

void GA_Individual::setGene(std::map<int, std::vector<int>> newGene)
{
    Gene = newGene;
    isEvaluated = false;
}

std::map<int, std::vector<int>> GA_Individual::getGenes() const
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
            for (auto &gSlot : g.second)
                {
                indiv += std::to_string(gSlot);
                indiv += " ";
                }
            }

        return indiv;
        }
}
