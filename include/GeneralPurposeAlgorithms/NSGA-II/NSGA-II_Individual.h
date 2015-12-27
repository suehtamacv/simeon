#ifndef NSGAII_INDIVIDUAL_H
#define NSGAII_INDIVIDUAL_H

#include <map>
#include <vector>
#include "NSGA-II_Parameter.h"

class Individual {
  public:
    Individual() : isEvaluated(false), crowdingDistance(-1), paretoFront(-1) {}

    bool isDominated(Individual &other);

    void eval();
    bool isEvaluated;

    double crowdingDistance;
    int paretoFront;

    double getCost(Parameter::PossibleParameters);

  private:
    std::vector<int> Gene;
    std::map<Parameter::PossibleParameters, double> Costs;
};

double Individual::getCost(Parameter::PossibleParameters param) {
    return Costs[param];
}

bool Individual::isDominated(Individual &other) {
    bool isDominated = true;

    for (auto cost : Costs) {
        isDominated &= (cost.second < other.getCost(cost.first));
    }

    return isDominated;
}

#endif // NSGAII_INDIVIDUAL_H

