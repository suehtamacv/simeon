#ifndef SIMULATION_REGENERATORNUMBER_H
#define SIMULATION_REGENERATORNUMBER_H

#include "SimulationType.h"
#include <SimulationTypes/NetworkSimulation.h>
#include <SimulationTypes/SimulationType.h>
#include <vector>
#include "RWA.h"

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

    double OptimizationLoad;
    long NumCalls;

    unsigned long minRegNumber;
    unsigned long maxRegNumber;
    unsigned long stepRegNumber;
    unsigned int numTranslucentNodes;

    RoutingAlgorithm::RoutingAlgorithms
    Routing_Algorithm;
    WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms
    WavAssign_Algorithm;
    RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    void createSimulations();
    void placeRegenerators(std::shared_ptr<Topology>);
    void refreshRegenerators(std::shared_ptr<Topology>, unsigned long numReg);
    std::vector<std::shared_ptr<NetworkSimulation>> simulations;
};

#endif // SIMULATION_REGENERATORNUMBER_H
