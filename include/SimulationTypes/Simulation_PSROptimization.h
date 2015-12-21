#ifndef SIMULATION_PSROPTIMIZATION_H
#define SIMULATION_PSROPTIMIZATION_H

#include <SimulationTypes/SimulationType.h>
#include <GeneralPurposeAlgorithms/PSO.h>

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

    class Compare {
    public:
    	bool operator()(long double a, long double b) {
    		return a < b;
    	}
    };

    class Fitness {
    public:
    	long double operator()(std::shared_ptr<PSO::PSO_Particle<long double>>);
    };
};

#endif // SIMULATION_PSROPTIMIZATION_H
