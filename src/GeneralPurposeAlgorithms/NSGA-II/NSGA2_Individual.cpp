#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.h>
#include <GeneralClasses/RandomGenerator.h>
#include <gtest/gtest.h>
#include <iostream>

using namespace NSGA_II;

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

std::string NSGA2_Individual::print(bool pretty)
{
    if (pretty)
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
        return "";
        }
    else
        {
        std::string indiv = "";
        for (auto &p : Parameters)
            {
            indiv += std::to_string(p->evaluate());
            indiv += " ";
            }

        for (auto &g : Gene)
            {
            indiv += std::to_string(g);
            indiv += " ";
            }
        return indiv;
        }
}

std::shared_ptr<NSGA2_Parameter> NSGA2_Individual::getParameter(
    unsigned int i) const
{
    EXPECT_LT(i, Parameters.size()) << "Invalid parameter requested";
    return Parameters[i];
}

double NSGA2_Individual::getParameterValue(unsigned int i) const
{
    EXPECT_LT(i, Parameters.size()) << "Invalid parameter requested";
    return Parameters[i]->evaluate();
}

unsigned int NSGA2_Individual::getNumParameters() const
{
    return Parameters.size();
}

bool NSGA2_Individual::isDominatedBy
(const std::shared_ptr<NSGA2_Individual> other) const
{
    for (unsigned int par1 = 0; par1 < Parameters.size(); par1++)
        {
        if (other->getParameter(par1)->evaluate() < getParameter(par1)->evaluate())
            {
            bool Dominates = true;

            for (unsigned par2 = 0; par2 < Parameters.size() && Dominates; par2++)
                {
                Dominates = Dominates &&
                            (other->getParameter(par2)->evaluate() <= getParameter(par2)->evaluate());
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
    crowdingDistance = paretoFront = -1;
    Gene = newGene;
}

std::vector<int> NSGA2_Individual::getGenes() const
{
    return Gene;
}
