#ifndef GA_H
#define GA_H

#include <memory>
#include <vector>

//! Contains the simple genetic algorithm
namespace GeneticAlgorithm
{

class GA_Generation;

/**
 * @brief The GA class contains a simple genetic algorithm, similar to the NSGA-II
 * algorithm but simpler in nature, as this algorithm isn't multiobjective.
 */
class GA
{
public:
    /**
     * @brief GA is the standard constructor for the GA class.
     */
    GA();

    /**
     * @brief run_Generation runs a generation.
     *
     * If it's being called by the first time, creates the initial generation.
     * Then, from the last generation, creates a new one (by breeding and mutating),
     * and the best Individuals from those two generations (classified by their
     * parameters and their Pareto Front) are selected to form the next generation.
     */
    void run_Generation();
    /**
     * @brief createInitialGeneration creates numIndiv Individuals to form the
     * first generation.
     */
    virtual void createInitialGeneration() = 0;

    /**
     * @brief mutationProb is the probability of mutation of each Individual's gene.
     */
    static constexpr double mutationProb = 0.1;
    /**
     * @brief breedingProb is the probability of breeding between Individuals.
     */
    static constexpr double breedingProb = 1;
    /**
     * @brief numGen is the number of generations run by the NSGA2.
     */
    static constexpr unsigned int numGen = 300;
    /**
     * @brief numIndiv is the number of Individuals in each generation.
     */
    static constexpr unsigned int numIndiv = 100;
    /**
     * @brief binaryTournamentParameter is a parameter to the Binary Tournament,
     * that takes part in the Selection process. Each Individual is tested against
     * binaryTournamentParameter other Individuals.
     */
    static constexpr unsigned int binaryTournamentParameter = 2;

protected:
    /**
     * @brief natural_selection uses binaryTournament to select numIndiv fit
     * Individuals from gen and copy them into dest.
     * @param gen is the origin Generation.
     * @param dest is the destination Generation.
     */
    void natural_selection(GA_Generation &gen, GA_Generation &dest);
    std::vector<std::shared_ptr<GA_Generation>> evolution;

    std::shared_ptr<GA_Generation> newGeneration(GA_Generation &prnt);

    unsigned int generation;
};
}

#endif // GA_H
