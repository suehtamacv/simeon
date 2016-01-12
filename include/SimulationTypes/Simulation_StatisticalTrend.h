#ifndef SIMULATION_BOXPLOT_H
#define SIMULATION_BOXPLOT_H

#include "SimulationType.h"
#include <RWA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RWA/WavelengthAssignmentAlgorithms/WavelengthAssignmentAlgorithm.h>
#include <RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>
#include <RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>

class NetworkSimulation;

class Simulation_StatisticalTrend : public SimulationType
{
public:
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

    RoutingAlgorithm::RoutingAlgorithms
    Routing_Algorithm;
    WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms
    WavAssign_Algorithm;
    RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    void create_Simulations();
    void place_Regenerators(std::shared_ptr<Topology>);

    bool hasLoaded;
};

#endif // SIMULATION_BOXPLOT_H
