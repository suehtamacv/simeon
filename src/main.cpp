#include <Structure/Topology.h>
#include <Calls/CallGenerator.h>
#include <Calls/Call.h>
#include <GeneralClasses/TransmissionBitrate.h>
#include <RWA/RoutingWavelengthAssignment.h>
#include <RWA/Routing/StaticRouting/ShortestPath.h>
#include <RWA/RegeneratorPlacement/NodalDegreeFirst.h>
#include <RWA/WavelengthAssignment/FirstFit.h>

int main(void) {
    auto T = std::shared_ptr<Topology>(new Topology());

    T->read_Topology("NSFNet");

    std::vector<ModulationScheme> Schemes;
    Schemes.push_back(ModulationScheme(4, Gain(6.8)));
    Schemes.push_back(ModulationScheme(16, Gain(10.5)));
    Schemes.push_back(ModulationScheme(64, Gain(14.8)));

    std::shared_ptr<RoutingAlgorithm> SP(new ShortestPath(T));
    std::shared_ptr<WavelengthAssignmentAlgorithm> FF(new FirstFit(T));

    CallGenerator CG(T, 1, 100);

    RoutingWavelengthAssignment RWA = RoutingWavelengthAssignment(SP, FF,
                                      Schemes, T);

    for (int i = 0 ; i < 5; i++) {
        Call C = CG.generate_Call(TransmissionBitrate(100E9));
        RWA.routeCall(C);
    }

    return 0;
}
