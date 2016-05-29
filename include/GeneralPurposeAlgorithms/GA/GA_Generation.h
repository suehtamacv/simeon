#ifndef GA_GENERATION_H
#define GA_GENERATION_H

#include "GA.h"

namespace GeneticAlgorithm
{

class GA_Individual;

/**
 * @brief The GA_Generation class represents a generation to the Genetic Algorithm.
 */
class GA_Generation
{
    friend class GA;

public:
    /**
     * @brief GA_Generation is the standard constructor.
     */
    GA_Generation();

    /**
     * @brief eval evaluates the parameters of each Generation's Individuals.
     */
    void eval();
    /**
     * @brief print prints the fitter individual.
     */
    void print(std::string filename = "NO_FILE_GIVEN");

    /**
     * @brief operator += clones the Individual i and adds it to this Generation.
     * @param i is the Individual to be added.
     */
    void operator +=(std::shared_ptr<GA_Individual> i);
    /**
     * @brief operator += clones each individual in Generation g and adds it to
     * this Generation.
     * @param g is the Generation to be added.
     */
    void operator += (std::shared_ptr<GA_Generation> g);

    /**
     * @brief binaryTournament does binaryTournament in the remaining Individuals
     * and returns a fit Individual.
     * @return a fit Individual.
     */
    std::shared_ptr<GA_Individual> binaryTournament();
    /**
     * @brief people is a set containing the individuals of this generation.
     */
    std::vector<std::shared_ptr<GA_Individual>> people;
    /**
     * @brief getBestIndividual returns the best individual of this generation.
     * @return the best individual of this generation.
     */
    std::shared_ptr<GA_Individual> getBestIndividual() const;

protected:
    bool isEvaluated;

    void breed(unsigned int a, unsigned int b, std::shared_ptr<GA_Generation> dest);
};
}

#endif // GA_GENERATION_H
