#ifndef NSGA2_GENERATION_H
#define NSGA2_GENERATION_H

#include <vector>
#include <memory>

class NSGA2_Individual;

/**
 * @brief The NSGA2_Generation class represents a single generation of NSGA2.
 */
class NSGA2_Generation
{
    friend class NSGA2;

public:
    /**
     * @brief NSGA2_Generation is the standard constructor.
     */
    NSGA2_Generation();

    /**
     * @brief eval evaluates the parameters of each Generation's Individuals, and
     * then sorts them into their Pareto Fronts and lastly evaluates their
     * Crowding Distance into each Front.
     */
    void eval();
    /**
     * @brief print prints all individuals in a certain Pareto Front.
     * @param paretoFront is the Pareto Front to print.
     */
    void print(std::string filename = "NO_FILE_GIVEN", int paretoFront = 1);

    /**
     * @brief operator += clones the Individual i and adds it to this Generation.
     * @param i is the Individual to be added.
     */
    void operator +=(std::shared_ptr<NSGA2_Individual> i);
    /**
     * @brief operator += clones each individual in Generation g and adds it to
     * this Generation.
     * @param g is the Generation to be added.
     */
    void operator += (std::shared_ptr<NSGA2_Generation> g);

    /**
     * @brief getParetoFront returns a vector with all Individuals in the i-th
     * Pareto Front.
     * @param i is the i-th Pareto Front.
     * @return a vector with all Individuals in the i-th Pareto Front.
     */
    std::vector<std::shared_ptr<NSGA2_Individual>> getParetoFront(int i);
    /**
     * @brief binaryTournament does binaryTournament in the remaining Individuals
     * and returns a fit Individual.
     * @return a fit Individual.
     */
    std::shared_ptr<NSGA2_Individual> binaryTournament();

protected:
    bool isEvaluated;

    std::vector<std::shared_ptr<NSGA2_Individual>> people;
    void evalCrowdingDistances(int ParetoFront);
    void evalCrowdingDistances();
    void evalParetoFront();

    void breed(NSGA2_Individual &a, NSGA2_Individual &b, NSGA2_Generation &dest);
};

#endif // NSGA2_GENERATION_H
