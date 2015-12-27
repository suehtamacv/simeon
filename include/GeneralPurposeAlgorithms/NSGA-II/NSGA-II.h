#ifndef NSGAII_H
#define NSGAII_H

#include "NSGA-II_Individual.h"
#include "NSGA-II_Parameter.h"

class NSGAII {
  public:
    NSGAII();
    std::vector<std::vector<Individual>> Generations;

};

#endif // NSGAII_H

