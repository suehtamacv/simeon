#ifndef SIMULATION_NETWORKLOAD_H
#define SIMULATION_NETWORKLOAD_H

#include <memory>
#include <vector>
#include <SimulationTypes/NetworkSimulation.h>
#include <SimulationTypes/SimulationType.h>
#include "RMSA.h"

namespace Simulations
{

/**
 * @brief The Simulation_NetworkLoad class is the simulation that varies the
 * network load and analyses the effect on the call blocking probability.
 *
 * This simulation varies the network load, and analyzes the network performance
 * in terms of predefined metrics, such as call blocking probability,
 * or slot blocking probability.
 */
class Simulation_NetworkLoad : public SimulationType
{
public:
    /**
     * @brief Simulation_NetworkLoad is the default constructor.
     */
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

    ROUT::RoutingAlgorithm::RoutingAlgorithms Routing_Algorithm;
    SA::SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithms
    WavAssign_Algorithm;
    RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    void create_Simulations();
    void place_Regenerators(std::shared_ptr<Topology> T);
};

}
#endif // SIMULATION_NETWORKLOAD_H
