#ifndef SIMULATION_NSGA2_REGENERATORPLACEMENT_H
#define SIMULATION_NSGA2_REGENERATORPLACEMENT_H

#include "../SimulationType.h"
#include <GeneralPurposeAlgorithms/NSGA-2.h>
#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RMSA/SpectrumAssignmentAlgorithms/SpectrumAssignmentAlgorithm.h>
#include <RMSA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>

namespace Simulations
{

/**
 * @brief The Simulation_NSGA2_RegnPlac class runs MORP regenerator placement
 * algorithm. This simulation uses the NSGA-2 genetic algorithm to find a
 * suitable set of transparent and translucent nodes, in order to fit
 * simultaneously call blocking probability, CapEx and OpEx constraints.
 */
class Simulation_NSGA2_RegnPlac : public SimulationType
{
public:
    /**
     * @brief Simulation_NSGA2_RegnPlac is the standard constructor for this
     * topology.
     */
    Simulation_NSGA2_RegnPlac();

    void help();
    void run();
    void load();
    void save(std::string);
    void load_file(std::string);
    void print();

    /**
     * @brief NumCalls is the number of calls that must be simulated by each
     * individual on the NSGA2 Optimization.
     */
    double NumCalls;
    /**
     * @brief NetworkLoad is the network load, in Erlangs, over which the simulation
     * of each individual is run.
     */
    double NetworkLoad;

    /**
     * @brief Routing_Algorithm is the routing algorithm used by the network simulation
     * of each individual.
     */
    RMSA::ROUT::RoutingAlgorithm::RoutingAlgorithms Routing_Algorithm;
    /**
     * @brief Routing_Cost is the routing cost used by the network simulation of
     * each individual.
     */
    RMSA::ROUT::RoutingCost::RoutingCosts Routing_Cost;
    /**
     * @brief WavAssign_Algorithm is the wavelength assignment algorithm used by
     * the network simulation of each individual.
     */
    RMSA::SA::SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithms
    WavAssign_Algorithm;
    /**
     * @brief RegAssignment_Algorithm is the regenerator assignment algorithm used
     * by the network simulation of each individual.
     */
    RMSA::RA::RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

private:
    bool hasLoaded;
    static unsigned int RegnMax;
    std::string FileName;

    class Individual;
    class Sim_NSGA2;
};

class Simulation_NSGA2_RegnPlac::Individual : public NSGA_II::NSGA2_Individual
{
    friend class Simulation_NSGA2_RegnPlac;

public:
    Individual(Simulation_NSGA2_RegnPlac &Sim) : Sim(Sim) {}
    void createIndividual();
    int createGene(unsigned int i);
    void setGene(std::vector<int> gene);
    std::shared_ptr<NSGA2_Individual> clone();

private:
    Simulation_NSGA2_RegnPlac &Sim;
};

class Simulation_NSGA2_RegnPlac::Sim_NSGA2 : public NSGA_II::NSGA2
{
    friend class Simulation_NSGA2_RegnPlac;

public:
    Sim_NSGA2(Simulation_NSGA2_RegnPlac &Sim);
    void createInitialGeneration();

private:
    Simulation_NSGA2_RegnPlac &Sim;
};

}

#endif // SIMULATION_NSGA2_REGENERATORPLACEMENT_H
