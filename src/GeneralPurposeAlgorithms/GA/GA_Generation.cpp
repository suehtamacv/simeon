#include "include/GeneralPurposeAlgorithms/GA/GA_Generation.h"
#include "include/GeneralPurposeAlgorithms/GA/GA_Individual.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace GeneticAlgorithm;

GA_Generation::GA_Generation()
{
    isEvaluated = false;
}

void GA_Generation::eval()
{
    if (isEvaluated)
        {
        return;
        }

    #pragma omp parallel for ordered schedule(dynamic)
    for (size_t i = 0; i < people.size(); i++)
        {
        auto person = people.begin();
        std::advance(person, i);
        (*person)->eval();
        }
    std::sort(people.begin(), people.end(),
              [](const std::shared_ptr<GA_Individual> &l,
                 const std::shared_ptr<GA_Individual> &r)
        {
        return *l < *r;
        });

    isEvaluated = true;
}

void GA_Generation::operator +=(std::shared_ptr<GA_Individual> i)
{
    isEvaluated = false;
    people.push_back(i->clone());
}

void GA_Generation::operator +=(std::shared_ptr<GA_Generation> g)
{
    for (auto &indiv : g->people)
        {
        this->operator +=(indiv);
        }
}

void GA_Generation::print(std::string filename)
{
    if (filename == "NO_FILE_GIVEN")
        {
        getBestIndividual()->print();
        }
    else
        {
        std::ofstream OutFile(filename.c_str());
        OutFile << getBestIndividual()->print(false) << std::endl;
        OutFile.close();
        }
}

std::shared_ptr<GA_Individual> GA_Generation::getBestIndividual() const
{
    std::shared_ptr<GA_Individual> best = people.front();
    for (auto &indiv : people)
        {
        if (indiv->getParameter() == -1)
            {
            indiv->eval();
            }

        if (indiv->getParameter() < best->getParameter())
            {
            best = indiv;
            }
        }
    return best;
}
