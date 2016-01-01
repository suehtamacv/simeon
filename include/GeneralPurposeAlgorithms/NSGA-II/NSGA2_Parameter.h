#ifndef NSGA2_PARAMETER_H
#define NSGA2_PARAMETER_H

#include <vector>

class NSGA2_Parameter {
    friend class NSGA2;

  public:
    NSGA2_Parameter(std::vector<int> gene);
    virtual double evaluate() = 0;
    bool operator == (const NSGA2_Parameter &other) const;

  protected:
    bool isEvaluated;
    double value;
    std::vector<int> gene;
};

#endif // NSGA2_PARAMETER_H
