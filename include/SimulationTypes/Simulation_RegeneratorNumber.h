#ifndef SIMULATION_REGENERATORNUMBER_H
#define SIMULATION_REGENERATORNUMBER_H

#include "SimulationType.h"

class Simulation_RegeneratorNumber : public SimulationType {
  public:
    Simulation_RegeneratorNumber();

    void help();
    void run();
    void load();
    void save(std::string);
    void load_file(std::string);
    void print();

  private:
    bool hasLoaded;
};

#endif // SIMULATION_REGENERATORNUMBER_H
