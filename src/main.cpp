#include "GeneralClasses.h"
#include "Devices.h"
#include "Structure.h"
#include "Calls.h"
#include "RWA.h"
#include "SimulationTypes.h"
#include <iostream>

int main(void) {
    std::shared_ptr<Topology> T = std::shared_ptr<Topology>(new
                                  Topology("data/topologies/NSFNet"));

    Simulation_NetworkLoad Simulation(T);
    Simulation.load();

    std::shared_ptr<RoutingAlgorithm> MH(new MinimumHops(T));
    std::shared_ptr<WavelengthAssignmentAlgorithm> FF(new FirstFit(T));
    std::shared_ptr<RegeneratorAssignmentAlgorithm> FLR(new FirstLongestReach(T,
            ModulationScheme::DefaultSchemes));
    std::shared_ptr<RoutingWavelengthAssignment>
    RWA(new RoutingWavelengthAssignment(MH, FF, FLR,
                                        ModulationScheme::DefaultSchemes, T));

    std::shared_ptr<RegeneratorPlacementAlgorithm> MSU(new MostSimultaneouslyUsed(T,
            RWA, 80, 1E4,
            TransmissionBitrate::DefaultBitrates));
    MSU->placeRegenerators(200, 0);

    for (long double load = 80; load <= 80; load += 10) {
        std::shared_ptr<CallGenerator> CG(new CallGenerator(T, load,
                                          TransmissionBitrate::DefaultBitrates));
        NetworkSimulation Sim(CG, RWA, 1E4);
        std::cout << load << "\t" << Sim.get_CallBlockingProbability() << std::endl;
    }

    return 0;
}
