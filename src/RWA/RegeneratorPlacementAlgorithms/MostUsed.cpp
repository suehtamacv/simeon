#include <RWA/RegeneratorPlacementAlgorithms/MostUsed.h>
#include <boost/assert.hpp>
#include <SimulationTypes/NetworkSimulation.h>
#include <GeneralClasses/RandomGenerator.h>

MostUsed::MostUsed(std::shared_ptr<Topology> T,
                   std::shared_ptr<RoutingWavelengthAssignment> RWA,
                   double NetworkLoad,
                   long long unsigned NumCalls,
                   std::vector<TransmissionBitrate> Bitrates
                  ) :
    NX_RegeneratorPlacement(T),
    RWA(RWA),
    NetworkLoad(NetworkLoad),
    NumCalls(NumCalls),
    Bitrates(Bitrates) {

}

void MostUsed::placeRegenerators(unsigned N, unsigned X) {
    BOOST_ASSERT_MSG(RWA->RA_Alg != nullptr, "Regenerator Placement can only run"
                     " if a Regenerator Assignment Algorithm has been set.");

    for (auto node : T->Nodes) {
        node->set_NodeType(Node::OpaqueNode);
    }

    if ((N == 0) && (X == 0)) {
        N = NX_N;
        X = NX_X;
    }

    std::shared_ptr<CallGenerator> CG(new CallGenerator(T, NetworkLoad, Bitrates));
    std::shared_ptr<NetworkSimulation> Sim(
        new NetworkSimulation(CG, RWA, NumCalls));
    Sim->run();

    std::vector<std::shared_ptr<Node>> PossibleNodes;

    for (auto node : T->Nodes) {
        node->set_NodeType(Node::TransparentNode);
        node->set_NumRegenerators(0);
        PossibleNodes.push_back(node);
    }

    for (unsigned iter = 0; iter < N; iter++) {
        long long unsigned MaxUsed = 0;

        for (auto node : PossibleNodes) {
            if (MaxUsed < node->get_TotalNumRequestedRegenerators()) {
                MaxUsed  = node->get_TotalNumRequestedRegenerators();
            }
        }

        std::vector<std::shared_ptr<Node>> MaximalNodes;

        for (auto node : PossibleNodes) {
            if (MaxUsed  == node->get_TotalNumRequestedRegenerators()) {
                MaximalNodes.push_back(node);
            }
        }

        std::uniform_int_distribution<int> dist(0, MaximalNodes.size() - 1);

        auto ChosenNode = MaximalNodes.begin();
        std::advance(ChosenNode, dist(random_generator));
        (*ChosenNode)->set_NumRegenerators(X);
        (*ChosenNode)->set_NodeType(Node::TranslucentNode);

        for (auto node = PossibleNodes.begin(); node != PossibleNodes.end(); ++node) {
            if (*node == *ChosenNode) {
                PossibleNodes.erase(node);
                break;
            }
        }

    }
}
