#include <RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SignalQualityPrediction.h>
#include <RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SQP_NetworkSimulation.h>
#include <RWA/RoutingAlgorithms/StaticRouting/MinimumHops.h>
#include <RWA/WavelengthAssignmentAlgorithms/FirstFit.h>
#include <RWA/RoutingWavelengthAssignment.h>
#include <Calls.h>
#include <GeneralClasses/RandomGenerator.h>

SignalQualityPrediction::SignalQualityPrediction(std::shared_ptr<Topology> T,
        std::shared_ptr<RoutingWavelengthAssignment> RWA,
        double NetworkLoad,
        unsigned long long NumCalls,
        std::vector<TransmissionBitrate> Bitrates) :
    NX_RegeneratorPlacement(T), RWA(RWA), NetworkLoad(NetworkLoad),
    NumCalls(NumCalls), Bitrates(Bitrates)
{
    evaluateLNMax();
}

void SignalQualityPrediction::load()
{
    NX_RegeneratorPlacement::load();
}

void SignalQualityPrediction::placeRegenerators(unsigned N, unsigned X)
{
    if ((N == 0) && (X == 0))
        {
        N = NX_N;
        X = NX_X;
        }

    auto Generator = std::make_shared<CallGenerator>(T, NetworkLoad);
    SQP_NetworkSimulation NetwSim(Generator, RWA, NumCalls, this);
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
    auto MH = std::make_shared<MinimumHops>(T);

    for (auto &bitrate : Bitrates)
        {
        for (auto &scheme : ModulationScheme::DefaultSchemes)
            {

            auto BitSchemePair = std::make_pair(bitrate, scheme);
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
                    DummyCall->Scheme = scheme;

                    auto links = MH->route(DummyCall);
                    Signal S;

                    if ((links.size() > maxLN) &&
                            (TransparentSegment(links, scheme).bypass(S).get_OSNR() >=
                             scheme.get_ThresholdOSNR(bitrate)))
                        {
                        maxLN = links.size();
                        }
                    }
                }

            LNMax.emplace(BitSchemePair, maxLN);
            }
        }
}

unsigned SignalQualityPrediction::get_LNMax(TransmissionBitrate bitrate,
        ModulationScheme scheme)
{
    return LNMax.at(std::make_pair(bitrate, scheme));
}
