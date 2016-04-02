#ifndef SIMULATION_BOXPLOT_H
#define SIMULATION_BOXPLOT_H

#include "SimulationType.h"
#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RMSA/SpectrumAssignmentAlgorithms/SpectrumAssignmentAlgorithm.h>
#include <RMSA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>
#include <RMSA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>
#include <RMSA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>

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
    SA::SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithms
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
