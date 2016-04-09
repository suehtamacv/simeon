#ifndef SIMULATION_POWERRATIOTHRESHOLD_H
#define SIMULATION_POWERRATIOTHRESHOLD_H

#include <memory>
#include <vector>
#include <SimulationTypes/NetworkSimulation.h>
#include <SimulationTypes/SimulationType.h>
#include "RMSA.h"
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

    std::vector<std::shared_ptr<NetworkSimulation>> simulations;

    bool hasLoaded;
    bool runLoadNX;
    double NumCalls;
    double NetworkLoad;
    double MinPowerRatioThreshold, MaxPowerRatioThreshold, PowerRatioThresholdStep;

    std::string FileName;

    RMSA::ROUT::RoutingAlgorithm::RoutingAlgorithms Routing_Algorithm;
    RMSA::SA::SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithms
    WavAssign_Algorithm;
    RMSA::RP::RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    RMSA::RA::RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    void create_Simulations();
    void place_Regenerators(std::shared_ptr<Topology> T);
};

}
#endif // SIMULATION_POWERRATIOTHRESHOLD_H
