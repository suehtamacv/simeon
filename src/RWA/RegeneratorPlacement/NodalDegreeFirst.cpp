#include <RWA/RegeneratorPlacement/NodalDegreeFirst.h>

NodalDegreeFirst::NodalDegreeFirst(std::shared_ptr<Topology> T) :
    NX_RegeneratorPlacement(T) {

}

void NodalDegreeFirst::placeRegenerators(int N, int X) {
    std::vector<std::shared_ptr<Node>> PossibleNodes;

    for (auto node : T->Nodes) {
        PossibleNodes.push_back(node);
    }

    for (int iter = 0; iter < N; iter++) {
        std::map<int, int> NodeDegree;

        for (auto node : PossibleNodes) {
            NodeDegree.emplace(node->ID, 0);
        }


    }
}
