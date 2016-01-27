#ifndef SIMULATION_NETWORKLOAD_H
#define SIMULATION_NETWORKLOAD_H

#include <memory>
#include <vector>
#include <SimulationTypes/NetworkSimulation.h>
#include <SimulationTypes/SimulationType.h>
#include "RWA.h"

class Simulation_NetworkLoad : public SimulationType
{
public:
    Simulation_NetworkLoad();

    void help();
    void run();
    void load();
    void save(std::string);
    void load_file(std::string);
    void print();

private:
    std::vector<std::shared_ptr<NetworkSimulation>> simulations;
    bool hasSimulated;
    bool hasLoaded;
    bool runLoadNX;

    double NumCalls;
    double NetworkLoadMin, NetworkLoadMax, NetworkLoadStep;

    std::string FileName;

    RoutingAlgorithm::RoutingAlgorithms
    Routing_Algorithm;
    WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms
    WavAssign_Algorithm;
    RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    void create_Simulations();
    void place_Regenerators(std::shared_ptr<Topology> T);
};

#endif // SIMULATION_NETWORKLOAD_H
