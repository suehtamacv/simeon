#include <RWA/RegeneratorPlacementAlgorithms/NodalDegreeFirst.h>
#include <random>
#include <boost/assert.hpp>

NodalDegreeFirst::NodalDegreeFirst(std::shared_ptr<Topology> T) :
    NX_RegeneratorPlacement(T) {

}

void NodalDegreeFirst::placeRegenerators(unsigned N, unsigned X) {
    BOOST_ASSERT_MSG(N <= T->Nodes.size(), "Can't have more translucent nodes"
                     " than nodes");
    std::vector<std::shared_ptr<Node>> PossibleNodes;

    for (auto node : T->Nodes) {
        node->set_NumRegenerators(0);
        node->set_NodeType(Node::TransparentNode);
        PossibleNodes.push_back(node);
    }

    for (unsigned iter = 0; iter < N; iter++) {
        std::map<std::shared_ptr<Node>, int> NodeDegree;

        for (auto node : PossibleNodes) {
            NodeDegree.emplace(node, 0);
        }

        for (auto orig : PossibleNodes) {
            for (auto dest : PossibleNodes) {
                if (orig == dest) {
                    continue;
                }

                if (orig->hasAsNeighbour(dest)) {
                    NodeDegree[orig]++;
                }
            }
        }

        int MaxDegree = -1;

        for (auto node : NodeDegree) {
            if (node.second > MaxDegree) {
                MaxDegree = node.second;
            }
        }

        std::vector<std::shared_ptr<Node>> MaximalNodes;

        for (auto node : NodeDegree) {
            if (MaxDegree == node.second) {
                MaximalNodes.push_back(node.first);
            }
        }

        std::uniform_int_distribution<int> dist(0, MaximalNodes.size() - 1);
        std::default_random_engine generator;

        auto ChosenNode = MaximalNodes.begin();
        std::advance(ChosenNode, dist(generator));
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
