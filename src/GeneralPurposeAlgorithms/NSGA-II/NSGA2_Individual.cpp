#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.h>
#include <GeneralClasses/RandomGenerator.h>
#include <boost/assert.hpp>
#include <iostream>

NSGA2_Individual::NSGA2_Individual() :
    crowdingDistance(-1),
    paretoFront(-1),
    isEvaluated(false)
{

}

bool NSGA2_Individual::operator ==(const NSGA2_Individual &other) const
{
    return (Gene == other.Gene);
}

bool NSGA2_Individual::operator <(const NSGA2_Individual &other) const
{
    //This is less than other if its Pareto Front is inner, or iff they're in the
    //same Pareto Front and this has smaller crowding Distance.
    return ((paretoFront < other.paretoFront) ||
            ((paretoFront == other.paretoFront) &&
             (crowdingDistance < other.crowdingDistance)));
}

void NSGA2_Individual::eval()
{
    if (Gene.empty())
        {
        createIndividual();
        }

    if (!isEvaluated)
        {
        for (auto &parameter : Parameters)
            {
            parameter->evaluate();
            }
        }

    isEvaluated = true;
}

void NSGA2_Individual::print()
{
    std::cout << "Individual: ";

    for (auto &g : Gene)
        {
        std::cout << g << " ";
        }

    std::cout << std::endl;

    for (auto &p : Parameters)
        {
        std::cout << p->get_ParamName() << ": " << p->evaluate() << "  ";
        }

    std::cout << std::endl;
}

std::shared_ptr<NSGA2_Parameter> NSGA2_Individual::getParameter(
    unsigned int i) const
{
    BOOST_ASSERT_MSG(i < Parameters.size(), "Invalid parameter requested");
    return Parameters[i];
}

double NSGA2_Individual::getParameterValue(unsigned int i) const
{
    BOOST_ASSERT_MSG(i < Parameters.size(), "Invalid parameter requested");

    return Parameters[i]->evaluate();
}

unsigned int NSGA2_Individual::getNumParameters() const
{
    return Parameters.size();
}

bool NSGA2_Individual::dominates(const std::shared_ptr<NSGA2_Individual> other)
const
{
    for (unsigned int i = 0; i < Parameters.size(); i++)
        {
        if (getParameter(i)->evaluate() < other->getParameter(i)->evaluate())
            {
            bool Dominates = true;

            for (unsigned j = 0; j < Parameters.size(); j++)
                {
                Dominates &=
                    (getParameter(j)->evaluate() <= other->getParameter(j)->evaluate());
                }

            if (Dominates)
                {
                return true;
                }
            }
        }

    return false;
}

NSGA2_Individual &NSGA2_Individual::mutate()
{
    crowdingDistance = paretoFront = -1;
    std::uniform_real_distribution<double> dist(0, 1);


    for (unsigned int i = 0; i < Gene.size(); i++)
        {
        if (dist(random_generator) < NSGA2::mutationProb)   //mutates
            {
            Gene[i] = createGene(i);
            isEvaluated = false;
            }
        }

    return *this;
}

void NSGA2_Individual::setGene(std::vector<int> newGene)
{
    isEvaluated = false;
    Gene = newGene;
}

std::vector<int> NSGA2_Individual::getGenes() const
{
    return Gene;
}
