#include <RWA/RegeneratorPlacementAlgorithms/MostSimultaneouslyUsed.h>
#include <boost/assert.hpp>
#include <SimulationTypes/NetworkSimulation.h>

MostSimultaneouslyUsed::MostSimultaneouslyUsed(std::shared_ptr<Topology> T,
        std::shared_ptr<RoutingWavelengthAssignment> RWA,
        long double NetworkLoad,
        long long unsigned NumCalls,
        std::vector<TransmissionBitrate> Bitrates) :
    RegeneratorPlacementAlgorithm(T),
    RWA(RWA),
    NetworkLoad(NetworkLoad),
    NumCalls(NumCalls),
    Bitrates(Bitrates) {

}

void MostSimultaneouslyUsed::placeRegenerators(unsigned NumTotalReg, unsigned) {
    BOOST_ASSERT_MSG(RWA->RA_Alg != nullptr, "Regenerator Placement can only run"
                     " if a Regenerator Assignment Algorithm has been set.");

    for (auto node : T->Nodes) {
        node->set_NodeType(Node::OpaqueNode);
    }

    std::shared_ptr<CallGenerator> CG(new CallGenerator(T, NetworkLoad, Bitrates));
    std::shared_ptr<NetworkSimulation> Sim(
        new NetworkSimulation(CG, RWA, NumCalls));
    Sim->run();

    unsigned long long TotalSimultaneousUsed = 0;

    for (auto node : T->Nodes) {
        TotalSimultaneousUsed += node->get_NumMaxSimultUsedRegenerators();
    }

    for (auto node : T->Nodes) {
        int NumReg = round(NumTotalReg * node->get_NumMaxSimultUsedRegenerators() /
                           (long double) TotalSimultaneousUsed);

        if (NumReg != 0) {
            node->set_NodeType(Node::TranslucentNode);
            node->set_NumRegenerators(NumReg);
        } else {
            node->set_NodeType(Node::TransparentNode);
            node->set_NumRegenerators(0);
        }
    }

}

void MostSimultaneouslyUsed::load() {
    std::cout << "Enter with the number of regenerators to be distributed." << std::endl;

    int NumTotalReg;

    do {
        std::cin >> NumTotalReg;

        if(NumTotalReg < 1)
            std::cerr << "Invalid number." << std::endl << std::endl;
        else
            break;

    } while(1);

    std::cout << "Enter with the number of regenerators per node." << std::endl;

    int X;

    do {
        std::cin >> X;

        if(X < 1)
            std::cerr << "Invalid number." << std::endl << std::endl;
        else
            break;
    } while(1);

    placeRegenerators(NumTotalReg, X);
}
