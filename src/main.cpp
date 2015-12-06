#include <Structure/Topology.h>
#include <Calls/CallGenerator.h>
#include <Calls/Call.h>
#include <RWA/Routing/StaticRouting/ShortestPath.h>
#include <RWA/RegeneratorPlacement/NodalDegreeFirst.h>

int main(void) {
    auto T = std::shared_ptr<Topology>(new Topology());

    std::weak_ptr<Node> A = T->add_Node();
    std::weak_ptr<Node> B = T->add_Node();
    std::weak_ptr<Node> C = T->add_Node();

    T->add_Link(A, B, 100);
    T->add_Link(B, A, 100);
    T->add_Link(A, C, 250);
    T->add_Link(C, A, 250);

    T->print_Topology("here");

    ShortestPath SP = ShortestPath(T);
    NodalDegreeFirst NDF = NodalDegreeFirst(T);

    CallGenerator CG(*T, 1, 100);

    for (int i = 0 ; i < 5; i++) {
        Call C = CG.generate_Call();
        SP.route(C);
    }

    return 0;
}
