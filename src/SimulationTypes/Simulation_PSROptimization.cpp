#include <SimulationTypes/Simulation_PSROptimization.h>
#include <GeneralPurposeAlgorithms/PSO.h>

Simulation_PSROptimization::Simulation_PSROptimization() {

}

void Simulation_PSROptimization::help() {
    std::cout << "\t\tPSR OPTIMIZATION SIMULATION" << std::endl << std::endl <<
              "\tThis simulation runs the Particle Swarm Optimization algorithm"
              " to find a set of coefficients that minimize the call blocking"
              " probability of the network. Attention: this usually takes"
              " some time." << std::endl;
}

void Simulation_PSROptimization::load() {

}

void Simulation_PSROptimization::save(std::ofstream) {

}

void Simulation_PSROptimization::load_file(std::ifstream) {

}

void Simulation_PSROptimization::print() {

}

void Simulation_PSROptimization::run() {

}

long double Simulation_PSROptimization::Fitness::operator()(
    std::shared_ptr<PSO::PSO_Particle<double>>) {
    return 1;
}
