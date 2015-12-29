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

    double getParameterValue(unsigned int i) const;
    std::shared_ptr<NSGA2_Parameter> getParameter(unsigned int i) const;

    double crowdingDistance;
    int paretoFront;

    unsigned int getNumParameters() const;
    bool isDominated(const NSGA2_Individual &other) const;

    NSGA2_Individual &mutate();

  protected:
    bool isEvaluated;

    std::vector<int> Gene;
    std::vector<std::shared_ptr<NSGA2_Parameter>> Parameters;

    std::weak_ptr<NSGA2_Generation> generation;
};

#endif // NSGA2_INDIVIDUAL_H
