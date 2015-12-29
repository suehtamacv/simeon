#ifndef NSGA2_INDIVIDUAL_H
#define NSGA2_INDIVIDUAL_H

#include <memory>
#include <vector>

class NSGA2_Generation;
class NSGA2_Parameter;

class NSGA2_Individual {
  public:
    NSGA2_Individual(std::weak_ptr<NSGA2_Generation> generation);

    virtual void create() = 0;
    void eval();

  protected:
    bool isEvaluated;

    std::vector<int> Gene;
    std::vector<std::shared_ptr<NSGA2_Parameter>> Parameters;

    double crowdingDistance;
    int paretoFront;
    std::weak_ptr<NSGA2_Generation> generation;
};

#endif // NSGA2_INDIVIDUAL_H
