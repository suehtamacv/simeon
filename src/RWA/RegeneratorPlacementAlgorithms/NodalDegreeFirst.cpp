#include <RWA/RegeneratorPlacementAlgorithms/NodalDegreeFirst.h>
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
        std::map<int, int> NodeDegree;

        for (auto node : PossibleNodes) {
            NodeDegree.emplace(node->ID, 0);
        }

        for (auto orig : PossibleNodes) {
            for (auto dest : PossibleNodes) {
                if (orig == dest) {
                    continue;
                }

                if (orig->hasAsNeighbour(dest)) {
                    NodeDegree[orig->ID]++;
                }
            }
        }

        int MaxDegree = -1, MaxDegreeNode = PossibleNodes.front()->ID;

        for (auto node : NodeDegree) {
            if (node.second > MaxDegree) {
                MaxDegreeNode = node.first;
                MaxDegree = node.second;
            }
        }

        for (auto it = PossibleNodes.begin(); it != PossibleNodes.end(); ++it) {
            if ((*it)->ID != MaxDegreeNode) {
                continue;
            }

            (*it)->set_NumRegenerators(X);
            (*it)->set_NodeType(Node::TranslucentNode);
            PossibleNodes.erase(it);
            break;
        }
    }
}
