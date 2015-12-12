#include <Structure/Topology.h>
#include <Calls/CallGenerator.h>
#include <Calls/Call.h>
#include <GeneralClasses/TransmissionBitrate.h>
#include <RWA/RoutingWavelengthAssignment.h>
#include <RWA/Routing/LengthOccupationRoutingAvailability.h>
#include <RWA/Routing/StaticRouting/ShortestPath.h>
#include <RWA/RegeneratorPlacement/NodalDegreeFirst.h>
#include <RWA/WavelengthAssignment/FirstFit.h>
#include <SimulationTypes/NetworkSimulation.h>
#include <RWA/Route.h>
#include <iostream>

int main(void) {
    std::shared_ptr<Topology> T = std::shared_ptr<Topology>(new Topology("NSFNet"));

    std::vector<ModulationScheme> Schemes;
    Schemes.push_back(ModulationScheme(4, Gain(6.8)));
    Schemes.push_back(ModulationScheme(16, Gain(10.5)));
    Schemes.push_back(ModulationScheme(64, Gain(14.8)));


    std::vector<TransmissionBitrate> Bitrates;
    Bitrates.push_back(TransmissionBitrate(10E9));
    Bitrates.push_back(TransmissionBitrate(40E9));
    Bitrates.push_back(TransmissionBitrate(100E9));
    Bitrates.push_back(TransmissionBitrate(160E9));
    Bitrates.push_back(TransmissionBitrate(400E9));

    std::shared_ptr<RoutingAlgorithm> LORa(new LengthOccupationRoutingAvailability(T));
    std::shared_ptr<WavelengthAssignmentAlgorithm> FF(new FirstFit(T));
    std::shared_ptr<RoutingWavelengthAssignment>
    RWA(new RoutingWavelengthAssignment(LORa, FF, Schemes, T));

    for (long double load = 80; load <= 300; load += 10) {
        std::shared_ptr<CallGenerator> CG(new CallGenerator(T, load, Bitrates));
        NetworkSimulation Sim(CG, RWA, 1E5);
        std::cout << load << "\t" << Sim.get_CallBlockingProbability() << std::endl;
    }

    return 0;
}
