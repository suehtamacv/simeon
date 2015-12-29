#ifndef NSGA2_PARAMETER_H
#define NSGA2_PARAMETER_H

#include <vector>

class NSGA2_Parameter {
  public:
    NSGA2_Parameter(std::vector<int> gene);
    virtual double evaluate() = 0;

  protected:
    std::vector<int> gene;
};

#endif // NSGA2_PARAMETER_H
