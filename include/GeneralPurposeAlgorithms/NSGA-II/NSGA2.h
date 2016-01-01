#ifndef NSGA2_H
#define NSGA2_H

#include <vector>
#include <memory>

class NSGA2_Generation;

class NSGA2 {
  public:
    NSGA2();

    void run_Generation();
    virtual void createInitialGeneration() = 0;

    static constexpr double mutationProb = 0.1;
    static constexpr double breedingProb = 1;
    static constexpr unsigned int numGen = 300;
    static constexpr unsigned int numIndiv = 100;
    static constexpr unsigned int binaryTournamentParameter = 2;

  protected:
    void natural_selection(NSGA2_Generation &gen, NSGA2_Generation &dest);
    std::vector<std::shared_ptr<NSGA2_Generation>> evolution;

    void newGeneration(NSGA2_Generation &parent);

    unsigned int generation;
};

#endif // NSGA2_H

