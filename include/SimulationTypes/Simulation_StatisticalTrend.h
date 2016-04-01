#ifndef SIMULATION_BOXPLOT_H
#define SIMULATION_BOXPLOT_H

#include "SimulationType.h"
#include <RWA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RWA/WavelengthAssignmentAlgorithms/WavelengthAssignmentAlgorithm.h>
#include <RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>
#include <RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>
#include <RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>

namespace Simulations
{

class NetworkSimulation;

/**
 * @brief The Simulation_StatisticalTrend class represents a statistical trend
 * analysis.
 *
 * This simulation repeats a fixed-parameter network simulation, in order to
 * evaluate any statistical trends on the results.
 */
class Simulation_StatisticalTrend : public SimulationType
{
public:
    /**
     * @brief Simulation_StatisticalTrend is the default constructor.
     */
    Simulation_StatisticalTrend();

    void run();
    void load();
    void print();
    void save(std::string);
    void load_file(std::string);
    void help();

private:
    std::vector<std::shared_ptr<NetworkSimulation>> simulations;

    double NumCalls;
    double NetworkLoad;
    int NumRepetitions;

    std::string FileName;

    RoutingAlgorithm::RoutingAlgorithms
    Routing_Algorithm;
    WA::WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms
    WavAssign_Algorithm;
    RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    void create_Simulations();
    void place_Regenerators(std::shared_ptr<Topology>);

    bool hasLoaded;
    bool runLoadNX;
};

}
#endif // SIMULATION_BOXPLOT_H
