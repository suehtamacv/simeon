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
    //Generic readings.
    SimulationType::load();

    std::cout << std::endl << "-> Choose a network type." << std::endl;

    do {
        for (auto nettype : NetworkTypes.left) {
            std::cout << "(" << nettype.first << ")\t" << nettype.second << std::endl;
        }

        int Net_Type;
        std::cin >> Net_Type;

        if (std::cin.fail() || NetworkTypes.left.count((NetworkType) Net_Type) == 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Network Type." << std::endl;
            std::cout << std::endl << "-> Choose a network type." << std::endl;
        } else {
            Type = (NetworkType) Net_Type;
            break;
        }
    } while (1);

    //Routing Algorithm
    Routing_Alg = RoutingAlgorithm::define_RoutingAlgorithm();

    //Wavelength Assignment Algorithm
    WavAssign_Algorithm = WavelengthAssignmentAlgorithm::define_WavelengthAssignmentAlgorithm();

    std::cout << std::endl << "-> Define the number of calls." << std::endl;

    do {
        std::cin >> NumCalls;

        if (std::cin.fail() || NumCalls < 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of calls." << std::endl;
            std::cout << std::endl << "-> Define the number of calls." << std::endl;
        } else {
            break;
        }
    } while (1);
}

void Simulation_NetworkLoad::save(std::ofstream) {

}

void Simulation_NetworkLoad::load_file(std::ifstream) {
    hasLoaded = true;
}
