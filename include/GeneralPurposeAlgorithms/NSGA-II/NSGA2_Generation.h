#ifndef NSGA2_GENERATION_H
#define NSGA2_GENERATION_H

#include <vector>
#include <memory>

class NSGA2_Individual;

class NSGA2_Generation {
  public:
    NSGA2_Generation();
    void eval();

  private:
    bool isEvaluated;

    std::vector<std::shared_ptr<NSGA2_Individual>> people;
    void evalCrowdingDistances();
    void evalParetoFront();
};

#endif // NSGA2_GENERATION_H
