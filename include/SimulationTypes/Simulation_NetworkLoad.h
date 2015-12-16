#ifndef SIMULATION_NETWORKLOAD_H
#define SIMULATION_NETWORKLOAD_H

#include <memory>
#include <vector>
#include <SimulationTypes/NetworkSimulation.h>
#include <SimulationTypes/SimulationType.h>
#include "RWA.h"

class Simulation_NetworkLoad : public SimulationType {
  public:
    Simulation_NetworkLoad(std::shared_ptr<Topology> T);

    void help();
    void run();
    void load();
    void save(std::ofstream);
    void load_file(std::ifstream);
    void print();

  private:
    std::shared_ptr<Topology> T;
    std::vector<std::shared_ptr<NetworkSimulation>> simulations;
    bool hasSimulated;
    bool hasLoaded;

    long long NumCalls;

    RoutingAlgorithm::RoutingAlgorithms Routing_Algorithm;
};

#endif // SIMULATION_NETWORKLOAD_H
