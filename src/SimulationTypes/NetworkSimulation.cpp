#include <SimulationTypes/NetworkSimulation.h>

NetworkSimulation::NetworkSimulation(std::shared_ptr<CallGenerator> Generator,
                                     std::shared_ptr<RoutingWavelengthAssignment> RWA,
                                     unsigned long NumCalls) :
    Generator(Generator), RWA(RWA), NumCalls(NumCalls) {

}

void NetworkSimulation::run() {
    for (long unsigned call = 0; call < NumCalls; call++) {

    }
}
