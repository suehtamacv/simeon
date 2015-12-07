#include <Structure/Topology.h>
#include <Calls/CallGenerator.h>
#include <Calls/Call.h>
#include <RWA/Routing/StaticRouting/ShortestPath.h>
#include <RWA/RegeneratorPlacement/NodalDegreeFirst.h>

int main(void) {
    auto T = std::shared_ptr<Topology>(new Topology());

    T->read_Topology("NSFNet");

    ShortestPath SP = ShortestPath(T);
    NodalDegreeFirst NDF = NodalDegreeFirst(T);
    NDF.placeRegenerators(2,10);

    CallGenerator CG(T, 1, 100);

    for (int i = 0 ; i < 5; i++) {
        Call C = CG.generate_Call();
        SP.route(C);
    }

    return 0;
}
