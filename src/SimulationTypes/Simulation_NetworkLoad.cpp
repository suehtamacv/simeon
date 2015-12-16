#include <SimulationTypes/Simulation_NetworkLoad.h>
#include <iostream>

Simulation_NetworkLoad::Simulation_NetworkLoad(std::shared_ptr<Topology>T) {
    this->T = std::shared_ptr<Topology>(new Topology(*T));
    hasSimulated = hasLoaded = false;
}

void Simulation_NetworkLoad::help() {
    std::cout << "\t\tNETWORK LOAD SIMULATION" << std::endl << std::endl <<
              "\tThis simulation varies the network load, and analyzes the"
              " network performance in terms of predefined metrics, such"
              " as call blocking probability, or slot blocking probability." << std::endl;
}

void Simulation_NetworkLoad::run() {
    if (!hasLoaded) {
        load();
    }

    for (auto simulation : simulations) {
        simulation->run();
    }
}

void Simulation_NetworkLoad::print() {
    std::cout << "Results:" << std::endl;
    std::cout << "LOAD\tCALL BLOC. PROB" << std::endl;

    if (!hasSimulated) {
        for (auto simulation : simulations) {
            simulation->run();
            simulation->print();
        }
    } else {
        for (auto simulation : simulations) {
            simulation->print();
        }
    }
}

void Simulation_NetworkLoad::load() {
    SimulationType::load();

    hasLoaded = true;
}

void Simulation_NetworkLoad::save(std::ofstream) {

}

void Simulation_NetworkLoad::load_file(std::ifstream) {
    hasLoaded = true;
}
