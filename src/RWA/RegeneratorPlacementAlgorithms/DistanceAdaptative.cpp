#include <RWA/RegeneratorPlacementAlgorithms/DistanceAdaptative.h>
#include <Structure/Link.h>
#include <Structure/Topology.h>
#include <Structure/Node.h>

int DistanceAdaptative::DA_NumTotalRegenerators;

DistanceAdaptative::DistanceAdaptative(std::shared_ptr<Topology> T) :
    RegeneratorPlacementAlgorithm(T)
{

}

void DistanceAdaptative::load()
{
    std::cout << std::endl << "-> Define the total number of regenerators."
              << std::endl;

    do
        {
        int NumTotalReg;
        std::cin >> NumTotalReg;

        if (std::cin.fail() || NumTotalReg < 1)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number." << std::endl;
            std::cout << std::endl << "-> Define the total number of regenerators."
                      << std::endl;
            }
        else
            {
            DA_NumTotalRegenerators = NumTotalReg;
            break;
            }

        }
    while (1);
}

void DistanceAdaptative::placeRegenerators(unsigned NumTotalReg, unsigned)
{
    if (NumTotalReg == 0)
        {
        NumTotalReg = DA_NumTotalRegenerators;
        }

    double TotalLinkLength = 0;
    for (auto &link : T->Links)
        {
        TotalLinkLength += link.second->Length;
        }

    for (auto &node : T->Nodes)
        {
        double NodeLinksLength = 0;
        for (auto &link : node->Links)
            {
            NodeLinksLength += link->Length;
            }

        int NumReg = std::floor(NumTotalReg * (NodeLinksLength / TotalLinkLength));
        if (NumReg == 0)
            {
            node->set_NodeType(Node::TransparentNode);
            node->set_NumRegenerators(0);
            }
        else
            {
            node->set_NodeType(Node::TranslucentNode);
            node->set_NumRegenerators(NumReg);
            }
        }
}
