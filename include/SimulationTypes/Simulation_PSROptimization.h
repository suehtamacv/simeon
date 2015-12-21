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

    std::shared_ptr<PowerSeriesRouting> MasterPSR;
    WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms
    WavAssign_Algorithm;
    RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    long double NumCalls;
    long double OptimizationLoad;

    class Compare {
      public:
        bool operator()(double a, double b) {
            return a < b;
        }
    };

    struct Fitness {
        long double operator()(std::shared_ptr<PSO::PSO_Particle<double>>);
    };
};

#endif // SIMULATION_PSROPTIMIZATION_H
