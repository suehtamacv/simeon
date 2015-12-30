#ifndef NSGA2_GENERATION_H
#define NSGA2_GENERATION_H

#include <vector>
#include <memory>

class NSGA2_Individual;

class NSGA2_Generation {
    friend class NSGA2;

  public:
    NSGA2_Generation();
    void eval();

    NSGA2_Generation &operator += (std::shared_ptr<NSGA2_Individual> &);
    NSGA2_Generation &operator += (NSGA2_Generation &);

    std::vector<std::shared_ptr<NSGA2_Individual>> getParetoFront(int i);
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
