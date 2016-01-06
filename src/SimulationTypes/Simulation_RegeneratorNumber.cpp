#include <SimulationTypes/Simulation_RegeneratorNumber.h>

Simulation_RegeneratorNumber::Simulation_RegeneratorNumber() :
    hasLoaded(false) {

}

void Simulation_RegeneratorNumber::help() {
    std::cout << "\t\tNUMBER OF REGENERATORS" << std::endl << std::endl <<
              "This simulation inserts regenerators in the nodes of the "
              " topology, and analyses the call requisition blocking probability."
              " If the RP Algorithm is NX, then the same number of regenerators"
              " will be inserted in each node. Otherwise, the product N . X is"
              " distributed over the topology." << std::endl;
}

void Simulation_RegeneratorNumber::run() {
    if (!hasLoaded) {
        load();
    }
}

void Simulation_RegeneratorNumber::load() {
    //General readings
    SimulationType::load();

    hasLoaded = true;
}

void Simulation_RegeneratorNumber::save(std::string) {

}

void Simulation_RegeneratorNumber::load_file(std::string) {

}

void Simulation_RegeneratorNumber::print() {
    if (!hasLoaded) {
        load();
    }
}
