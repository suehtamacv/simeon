#ifndef SIMULATION_POWERRATIOTHRESHOLD_H
#define SIMULATION_POWERRATIOTHRESHOLD_H

#include <SimulationTypes/SimulationType.h>
#include <string>

namespace Simulations
{

class Simulation_PowerRatioThreshold : public SimulationType
{
public:
    Simulation_PowerRatioThreshold();

    void help();
    void run();
    void load();
    void save(std::string);
    void load_file(std::string);
    void print();
};

}
#endif // SIMULATION_POWERRATIOTHRESHOLD_H
