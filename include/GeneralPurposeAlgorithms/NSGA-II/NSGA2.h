#ifndef NSGA2_H
#define NSGA2_H

#include <vector>
#include <memory>

//! Non Sorting Genetic Algorithm II
namespace NSGA_II
{

class NSGA2_Generation;

/**
 * @brief The NSGA2 class implements the Non Sorting Genetic Algorithm II
 * (NSGA 2) Algorithm.
 *
 * More details on "A Fast Elitist Non-Dominated Sorting Genetic Algorithm for
 * Multi-Objective Optimization: NSGA-II", by Kalyanmoy Deb et al.
 **/
class NSGA2
{
public:
    /**
     * @brief NSGA2 is the standard constructor for a NSGA2 object.
     */
    NSGA2();

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
    void natural_selection(NSGA2_Generation &gen, NSGA2_Generation &dest);
    std::vector<std::shared_ptr<NSGA2_Generation>> evolution;

    std::shared_ptr<NSGA2_Generation> newGeneration(NSGA2_Generation &prnt);

    unsigned int generation;
};
}

#endif // NSGA2_H

