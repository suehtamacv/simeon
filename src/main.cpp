#include <Structure/Topology.h>
#include <Calls/CallGenerator.h>
#include <Calls/Call.h>

int main(void) {
    Topology T;

    std::weak_ptr<Node> A = T.add_Node();
    std::weak_ptr<Node> B = T.add_Node();
    std::weak_ptr<Node> C = T.add_Node();

    std::weak_ptr<Link> LAB = T.add_Link(A, B, 100);
    std::weak_ptr<Link> LAC = T.add_Link(A, C, 250);

    T.read_Topology("here");

    CallGenerator CG(T,1,100);
    for (int i = 0 ; i < 5; i++) {
        CG.generate_Call();
    }

    return 0;
}
