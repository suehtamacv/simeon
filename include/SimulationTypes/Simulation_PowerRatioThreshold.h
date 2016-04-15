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

/**
 * @brief The Simulation_PowerRatioThreshold class is the simulation
 * that varies the power ratio threshold and analyzes the effect on
 * the call blocking probability.
 *
 * This simulation varies the power ratio threshold for the filter
 * imperfection physical impairment, and analyzes the network
 * performance in terms of call blocking probability.
 */
class Simulation_PowerRatioThreshold : public SimulationType
{
public:
    /**
     * @brief Simulation_PowerRatioThreshold is the default constructor.
     */
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
    double PowerRatioThresholdMin, PowerRatioThresholdMax, PowerRatioThresholdStep;

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
