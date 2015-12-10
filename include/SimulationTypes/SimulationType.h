#ifndef SIMULATIONTYPE_H
#define SIMULATIONTYPE_H

#include <fstream>

class SimulationType {
  public:
    SimulationType();

    virtual void run() = 0;
    virtual void load() = 0;
    virtual void save(std::ofstream) = 0;
    virtual void load_file(std::ifstream) = 0;
};

#endif // SIMULATIONTYPE_H
