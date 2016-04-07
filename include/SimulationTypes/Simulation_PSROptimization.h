#ifndef SIMULATION_PSROPTIMIZATION_H
#define SIMULATION_PSROPTIMIZATION_H

#include <SimulationTypes/SimulationType.h>
#include <GeneralPurposeAlgorithms/PSO.h>
#include <RMSA/RoutingAlgorithms/PowerSeriesRouting/PowerSeriesRouting.h>
#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RMSA/SpectrumAssignmentAlgorithms/SpectrumAssignmentAlgorithm.h>
#include <RMSA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>
#include <RMSA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>

namespace Simulations
{

/**
 * @brief The Simulation_PSROptimization class is the PSR Optimization simulation.
 *
 * This simulation runs the Particle Swarm Optimization algorithm to find a set
 * of coefficients that minimize the call blocking probability of the network.
 */
class Simulation_PSROptimization : public SimulationType
{
public:
    /**
     * @brief Simulation_PSROptimization is the default constructor.
     */
    Simulation_PSROptimization();

    void help();
    void run();
    void load();
    void save(std::string);
    void load_file(std::string);
    void print();

private:
    bool hasLoaded;
    bool hasRun;

    std::shared_ptr<PSO_Particle<double>> BestParticle;

    ROUT::PSR::PowerSeriesRouting::Variants Variant;

    static SA::SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithms
    WavAssign_Algorithm;
    static RP::RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    static RA::RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    static double NumCalls;
    static double OptimizationLoad;

    int NMin;
    int NMax;
    static std::vector<std::shared_ptr<ROUT::PSR::Cost>> Costs;

    std::string CoefficientsFilename;
    std::string LogFilename;

    static constexpr unsigned int P = 48;
    static constexpr unsigned int G = 500;
    static constexpr double XMin = -1;
    static constexpr double XMax = 1;
    static constexpr double VMin = -1;
    static constexpr double VMax = 1;

    void create_Simulation();

    void runPSR();

    struct Compare
    {
        bool operator()(double a, double b)
        {
            return a < b;
        }
    };

    struct Fitness
    {
        static std::shared_ptr<Topology> T;
        static ROUT::PSR::PowerSeriesRouting::Variants Variant;
        double operator()(std::shared_ptr<PSO_Particle<double>>);
    };

    std::shared_ptr<ParticleSwarmOptimization<double, Fitness, Compare>>
            PSO_Optim;

    void printCoefficients(std::string file, bool override = true);
};

}

#endif // SIMULATION_PSROPTIMIZATION_H
