#include <RMSA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SignalQualityPrediction.h>
#include <RMSA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SQP_NetworkSimulation.h>
#include <RMSA/RoutingAlgorithms/Costs/MinimumHops.h>
#include <RMSA/RoutingAlgorithms/Costs/ShortestPath.h>
#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RMSA/SpectrumAssignmentAlgorithms/FirstFit.h>
#include <RMSA/RoutingWavelengthAssignment.h>
#include <GeneralClasses/RandomGenerator.h>
#include <Structure/Link.h>
#include <Calls.h>
#include <boost/assign.hpp>

using namespace RMSA::RP::SQP;

bool SignalQualityPrediction::chosenType = false;
SignalQualityPrediction::SQP_Type SignalQualityPrediction::Type;

SignalQualityPrediction::SQPTypeNameBimap
SignalQualityPrediction::SQPTypeNames =
    boost::assign::list_of<SignalQualityPrediction::SQPTypeNameBimap::relation>
#define X(a,b) (a,b)
    SQPTypes
#undef X
#undef SQPTypes
    ;


SignalQualityPrediction::SignalQualityPrediction(std::shared_ptr<Topology> T,
        std::shared_ptr<RoutingWavelengthAssignment> RMSA,
        double NetworkLoad,
        unsigned long long NumCalls,
        std::vector<TransmissionBitrate> Bitrates) :
    NX_RegeneratorPlacement(T), RMSA(RMSA), NetworkLoad(NetworkLoad),
    NumCalls(NumCalls), Bitrates(Bitrates)
{
    chooseSQPType();
    evaluateLNMax();
}

void SignalQualityPrediction::load()
{
    NX_RegeneratorPlacement::load();
}

void SignalQualityPrediction::chooseSQPType()
{
    if (chosenType)
        {
        return;
        }

    std::cout << std::endl << "-> Define the SQP Type." << std::endl;

    do
        {
        for (auto &type : SQPTypeNames.left)
            {
            std::cout << "(" << type.first << ")\t" << type.second << std::endl;
            }

        int chosenSQPType;
        std::cin >> chosenSQPType;

        if (std::cin.fail() || SQPTypeNames.left.count
                ((SQP_Type) chosenSQPType) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid SQP Type." << std::endl;
            std::cout << std::endl << "-> Define the SQP Type." << std::endl;
            }
        else
            {
            Type = (SQP_Type) chosenSQPType;
            chosenType = true;
            break;
            }
        }
    while (1);
}

void SignalQualityPrediction::placeRegenerators(unsigned N, unsigned X)
{
    if ((N == 0) && (X == 0))
        {
        N = NX_N;
        X = NX_X;
        }

    auto Generator = std::make_shared<CallGenerator>(T, NetworkLoad);
    SQP_NetworkSimulation NetwSim(Generator, RMSA, NumCalls, this);
    NetwSim.run();

    for (auto &node : T->Nodes)
        {
        node->set_NumRegenerators(0);
        node->set_NodeType(Node::TransparentNode);
        }

    for (unsigned iter = 0; iter < N; iter++)
        {
        std::map<std::shared_ptr<Node>, int> NodeUsage;

        for (auto &node : T->Nodes)
            {
            NodeUsage.emplace(node, NetwSim.NodeUsage[node->ID]);
            }

        int MaxUsage = -1;

        for (auto &node : NodeUsage)
            {
            if (node.second > MaxUsage)
                {
                MaxUsage = node.second;
                }
            }

        std::vector<std::shared_ptr<Node>> MaximalNodes;

        for (auto &node : NodeUsage)
            {
            if (MaxUsage == node.second)
                {
                MaximalNodes.push_back(node.first);
                }
            }

        std::uniform_int_distribution<int> dist(0, MaximalNodes.size() - 1);

        auto ChosenNode = MaximalNodes.begin();
        std::advance(ChosenNode, dist(random_generator));
        (*ChosenNode)->set_NumRegenerators(X);
        (*ChosenNode)->set_NodeType(Node::TranslucentNode);

        for (auto node = T->Nodes.begin(); node != T->Nodes.end(); ++node)
            {
            if (*node == *ChosenNode)
                {
                NetwSim.NodeUsage[(*node)->ID] = -1;
                break;
                }
            }
        }
}

void SignalQualityPrediction::evaluateLNMax()
{
    LNMax.clear();
    std::shared_ptr<ROUT::RoutingAlgorithm> R_Alg;
    auto WA_Alg =
        SA::SpectrumAssignmentAlgorithm::create_SpectrumAssignmentAlgorithm(
            SA::SpectrumAssignmentAlgorithm::FF, T);

    switch (Type)
        {
        case Distance:
            R_Alg = ROUT::RoutingAlgorithm::create_RoutingAlgorithm
                    (RMSA->R_Alg->RoutAlg, ROUT::RoutingCost::SP, T);
            break;

        case HopsNumber:
            R_Alg = ROUT::RoutingAlgorithm::create_RoutingAlgorithm
                    (RMSA->R_Alg->RoutAlg, ROUT::RoutingCost::MH, T);
            break;
        }

    for (auto &bitrate : Bitrates)
        {
        for (auto scheme = ModulationScheme::DefaultSchemes.rbegin();
                scheme != ModulationScheme::DefaultSchemes.rend(); ++scheme)
            {
            auto BitSchemePair = std::make_pair(bitrate, *scheme);
            unsigned maxLN = 0;

            for (auto &orig : T->Nodes)
                {
                for (auto &dest : T->Nodes)
                    {
                    if (orig == dest)
                        {
                        continue;
                        }

                    auto DummyCall = std::make_shared<Call>(orig, dest, bitrate);
                    DummyCall->Scheme = *scheme;

                    std::vector<std::weak_ptr<Link>> links = R_Alg->route(DummyCall).front();
                    TransparentSegment segment(links, *scheme, 0);
                    auto usedSlots = WA_Alg->assignSlots(DummyCall, segment);

                    Signal S(usedSlots);
                    unsigned long LNRoute = 0;

                    switch (Type)
                        {
                        case HopsNumber:
                            LNRoute = links.size();
                            break;

                        case Distance:
                            for (auto &link : links)
                                {
                                LNRoute += link.lock()->Length;
                                }
                            break;
                        }

                    if ((LNRoute > maxLN) &&
                            (segment.bypass(S).get_OSNR() >= scheme->get_ThresholdOSNR(bitrate)))
                        {
                        maxLN = LNRoute;
                        }
                    }
                }

            LNMax.emplace(BitSchemePair, maxLN);
            }
        }
}

double SignalQualityPrediction::get_LNMax(TransmissionBitrate bitrate,
        ModulationScheme scheme)
{
    return LNMax.at({bitrate, scheme});
}
