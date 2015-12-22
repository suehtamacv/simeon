#ifndef SIMULATION_PSROPTIMIZATION_H
#define SIMULATION_PSROPTIMIZATION_H

#include <SimulationTypes/SimulationType.h>
#include <GeneralPurposeAlgorithms/PSO.h>
#include <RWA/RoutingAlgorithms/PowerSeriesRouting/PowerSeriesRouting.h>

class Simulation_PSROptimization : public SimulationType {
  public:
    Simulation_PSROptimization();

    void help();
    void run();
    void load();
    void save(std::ofstream);
    void load_file(std::ifstream);
    void print();

  private:
    bool hasLoaded;
    bool hasRun;

    static std::shared_ptr<PowerSeriesRouting> MasterPSR;
    static WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms
    WavAssign_Algorithm;
    static RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    static RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    static double NumCalls;
    static double OptimizationLoad;

    static constexpr unsigned int P = 50;
    static constexpr unsigned int G = 500;
    static constexpr double XMin = -1;
    static constexpr double XMax = 1;
    static constexpr double VMin = -1;
    static constexpr double VMax = 1;

    void create_Simulation();

    struct Compare {
        bool operator()(double a, double b) {
            return a < b;
        }
    };

    struct Fitness {
        static std::shared_ptr<Topology> T;
        double operator()(std::shared_ptr<PSO::PSO_Particle<double>>);
    };
};

#endif // SIMULATION_PSROPTIMIZATION_H
