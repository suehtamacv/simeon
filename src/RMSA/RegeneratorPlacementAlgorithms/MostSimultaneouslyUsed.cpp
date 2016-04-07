#include <RMSA/RegeneratorPlacementAlgorithms/MostSimultaneouslyUsed.h>
#include <boost/assert.hpp>
#include <SimulationTypes/NetworkSimulation.h>
#include <Calls/CallGenerator.h>
#include <RMSA/RoutingWavelengthAssignment.h>

using namespace RMSA::RP;

unsigned MostSimultaneouslyUsed::MSU_NumTotalReg;

MostSimultaneouslyUsed::MostSimultaneouslyUsed(std::shared_ptr<Topology> T,
        std::shared_ptr<RoutingWavelengthAssignment> RMSA,
        double NetworkLoad,
        long long unsigned NumCalls,
        std::vector<TransmissionBitrate> Bitrates) :
    RegeneratorPlacementAlgorithm(T),
    RMSA(RMSA),
    NetworkLoad(NetworkLoad),
    NumCalls(NumCalls),
    Bitrates(Bitrates)
{

}

void MostSimultaneouslyUsed::placeRegenerators(unsigned NumTotalReg, unsigned)
{
    BOOST_ASSERT_MSG(RMSA->RA_Alg != nullptr, "Regenerator Placement can only run"
                     " if a Regenerator Assignment Algorithm has been set.");

    if (NumTotalReg == 0)
        {
        NumTotalReg = MSU_NumTotalReg;
        }

    for (auto &node : T->Nodes)
        {
        node->set_NodeType(Node::OpaqueNode);
        }

    auto CG = std::make_shared<CallGenerator>(T, NetworkLoad, Bitrates);
    auto Sim = std::make_shared<Simulations::NetworkSimulation>(CG, RMSA, NumCalls);
    Sim->run();

    unsigned long long TotalSimultaneousUsed = 0;

    for (auto &node : T->Nodes)
        {
        TotalSimultaneousUsed += node->get_NumMaxSimultUsedRegenerators();
        }

    for (auto &node : T->Nodes)
        {
        int NumReg = round(NumTotalReg * node->get_NumMaxSimultUsedRegenerators() /
                           (double) TotalSimultaneousUsed);

        if (NumReg != 0)
            {
            node->set_NodeType(Node::TranslucentNode);
            node->set_NumRegenerators(NumReg);
            }
        else
            {
            node->set_NodeType(Node::TransparentNode);
            node->set_NumRegenerators(0);
            }
        }

}

void MostSimultaneouslyUsed::load()
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
            MSU_NumTotalReg = NumTotalReg;
            break;
            }

        }
    while (1);
}
