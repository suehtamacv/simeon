#include <RMSA/RegeneratorPlacementAlgorithms/NodalDegreeFirst.h>
#include <random>
#include <gtest/gtest.h>

#include <GeneralClasses/RandomGenerator.h>
#include <Structure/Topology.h>

using namespace RMSA::RP;

NodalDegreeFirst::NodalDegreeFirst(std::shared_ptr<Topology> T) :
    NX_RegeneratorPlacement(T)
{

}

void NodalDegreeFirst::load()
{
    NX_RegeneratorPlacement::load();
}

void NodalDegreeFirst::placeRegenerators(unsigned N, unsigned X)
{
#ifdef RUN_ASSERTIONS
    EXPECT_LE(N, T->Nodes.size()) << "Can't have more translucent nodes than nodes";
#endif

    if ((N == 0) && (X == 0))
        {
        N = NX_N;
        X = NX_X;
        }

    std::map<int, std::shared_ptr<Node>> Nodes;
    std::vector<int> PossibleNodes;

    for (auto &node : T->Nodes)
        {
        node->set_NumRegenerators(0);
        node->set_NodeType(Node::TransparentNode);
        PossibleNodes.push_back(node->ID);
        Nodes.insert({node->ID, node});
        }

    for (unsigned iter = 0; iter < N; iter++)
        {
        std::map<int, int> NodeDegree;

        for (auto node : PossibleNodes)
            {
            NodeDegree.insert({node, 0});
            }

        for (auto &orig : PossibleNodes)
            {
            for (auto &dest : PossibleNodes)
                {
                if (Nodes[orig]->hasAsNeighbour(Nodes[dest]))
                    {
                    NodeDegree[orig]++;
                    }
                }
            }

        int MaxDegree = -1;

        for (auto &node : NodeDegree)
            {
            if (node.second > MaxDegree)
                {
                MaxDegree = node.second;
                }
            }

        auto chosenNode = Nodes[PossibleNodes.front()];

        for (auto &node : NodeDegree)
            {
            if (MaxDegree == node.second)
                {
                chosenNode = Nodes[node.first];
                break;
                }
            }

        chosenNode->set_NumRegenerators(X);
        chosenNode->set_NodeType(Node::TranslucentNode);

        for (auto node = PossibleNodes.begin(); node != PossibleNodes.end(); ++node)
            {
            if (*node == chosenNode->ID)
                {
                PossibleNodes.erase(node);
                break;
                }
            }
        }
}
