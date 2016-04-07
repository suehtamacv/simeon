#ifndef SIMULATION_REGENERATORNUMBER_H
#define SIMULATION_REGENERATORNUMBER_H

#include "SimulationType.h"
#include <SimulationTypes/NetworkSimulation.h>
#include <SimulationTypes/SimulationType.h>
#include <vector>
#include "RMSA.h"

namespace Simulations
{

/**
 * @brief The Simulation_RegeneratorNumber class represents a simulation that
 * varies the number of regenerators.
 *
 * This simulation inserts regenerators in the nodes of the  topology, and
 * analyses the call requisition blocking probability. If the RP Algorithm is NX,
 * then the same number of regenerators will be inserted in each node. Otherwise,
 * the product N . X of regenerators is distributed over the topology.
 */
class Simulation_RegeneratorNumber : public SimulationType
{
public:
    /**
     * @brief Simulation_RegeneratorNumber is the default constructor.
     */
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
    long double NumCalls;

    std::string FileName;

    unsigned long minRegNumber;
    unsigned long maxRegNumber;
    unsigned long stepRegNumber;
    unsigned int numTranslucentNodes;

    RMSA::ROUT::RoutingAlgorithm::RoutingAlgorithms Routing_Algorithm;
    RMSA::SA::SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithms
    WavAssign_Algorithm;
    RMSA::RP::RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    RMSA::RA::RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    void createSimulations();
    void placeRegenerators(std::shared_ptr<Topology>);
    void refreshRegenerators(std::shared_ptr<Topology>, unsigned long numReg);
    std::vector<std::shared_ptr<NetworkSimulation>> simulations;
};

}

#endif // SIMULATION_REGENERATORNUMBER_H
