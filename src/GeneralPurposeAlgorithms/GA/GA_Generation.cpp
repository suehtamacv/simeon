#include "include/GeneralPurposeAlgorithms/GA/GA_Generation.h"
#include "include/GeneralPurposeAlgorithms/GA/GA_Individual.h"
#include "include/GeneralClasses/RandomGenerator.h"
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
    for (unsigned i = 0; i < people.size(); i++)
        {
        auto person = people.begin();
        std::advance(person, i);
        (*person)->eval();
        }
    std::sort(people.begin(), people.end());

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

void GA_Generation::breed(unsigned int a, unsigned int b,
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

    std::uniform_real_distribution<double> dist(0, 1);
    std::vector<int> GeneA = (*iterator_a)->getGenes(),
                     GeneB = (*iterator_b)->getGenes();

    for (unsigned int i = 0; i < GeneA.size(); ++i)
        {
        if (dist(random_generator) < 0.5)
            {
            std::swap(GeneA[i], GeneB[i]); //swaps genes of the individuals
            }
        }

    auto newIndivA = (*iterator_a)->clone(), newIndivB = (*iterator_b)->clone();
    newIndivA->setGene(GeneA);
    newIndivB->setGene(GeneB);
    (*dest) += newIndivA;
    (*dest) += newIndivB;

    people.erase(iterator_a);
    people.erase(iterator_b);
}

void GA_Generation::print(std::string filename)
{
    if (filename == "NO_FILE_GIVEN")
        {
        (*(people.begin()))->print();
        }
    else
        {
        std::ofstream OutFile(filename.c_str());
        OutFile << (*(people.begin()))->print(false) << std::endl;
        OutFile.close();
        }
}
