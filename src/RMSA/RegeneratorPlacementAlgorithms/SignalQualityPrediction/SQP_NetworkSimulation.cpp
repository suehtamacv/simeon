#include <RMSA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SQP_NetworkSimulation.h>
#include <Calls.h>
#include <RMSA/TransparentSegment.h>
#include <RMSA/Route.h>
#include <RMSA/RoutingWavelengthAssignment.h>
#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <Structure/Topology.h>
#include <Structure/Link.h>

using namespace RMSA::RP::SQP;

SQP_NetworkSimulation::SQP_NetworkSimulation(std::shared_ptr<CallGenerator>
        Generator, std::shared_ptr<RoutingWavelengthAssignment> RMSA,
        unsigned long NumMaxCalls, SignalQualityPrediction *SQP) :
    NetworkSimulation(Generator, RMSA, NumMaxCalls), SQP(SQP)
{
    NodeUsage = std::vector<long int>(RMSA->T->Nodes.size() + 1, 0);
}

void SQP_NetworkSimulation::implement_call(std::shared_ptr<Event> evt)
{
    NetworkSimulation::implement_call(evt);

    auto Links = RMSA->R_Alg->route(evt->Parent);
    if (Links.empty())
        {
        return;
        }

    long int LNMax = 0;
    std::sort(ModulationScheme::DefaultSchemes.rbegin(),
              ModulationScheme::DefaultSchemes.rend());

    for (auto &scheme : ModulationScheme::DefaultSchemes)
        {
        LNMax = SQP->get_LNMax(evt->Parent->Bitrate, scheme);
        if (LNMax != 0)
            {
            break;
            }
        }

    if (LNMax == 0)
        {
        return;
        }

    std::vector<bool> sqp_LNMax(Links.size() + 1, false);

    //LNMax is based on Minimum Hops measure
    if (SQP->Type == SignalQualityPrediction::HopsNumber)
        {
        for (unsigned numNode = 0; numNode <= Links.size(); ++numNode)
            {
            if ((numNode % LNMax == 0) ||
                    ((numNode - 1) % LNMax == 0) ||
                    ((numNode + 1) % LNMax == 0))
                {
                sqp_LNMax[numNode] = true;
                }
            }
        }
    //LNMax is based on Shortest Path measure
    else if (SQP->Type == SignalQualityPrediction::Distance)
        {
        double sumLength = 0;
        int countLNMaxSection = 1;

        for (unsigned numNode = 0; numNode < Links.size(); ++numNode)
            {
            sumLength += Links[numNode].lock()->Length;
            if (sumLength >= countLNMaxSection * LNMax)
                {
                countLNMaxSection++;
                sqp_LNMax[numNode] = sqp_LNMax[numNode + 1] = true;
                numNode != 0 ? sqp_LNMax[numNode - 1] = true : 0;
                }
            }
        }

    for (unsigned numNode = 0; numNode < Links.size(); ++numNode)
        {
        if (sqp_LNMax[numNode])
            {
            NodeUsage[Links[numNode].lock()->Origin.lock()->ID]++;
            }
        }

    if (sqp_LNMax[Links.size()])
        {
        NodeUsage[Links.back().lock()->Destination.lock()->ID]++;
        }

}

void SQP_NetworkSimulation::run()
{
    NumCalls++;
    Generator->generate_Call(); //Generates first call

    while (!Generator->Events.empty())
        {
        std::shared_ptr<Event> evt(Generator->Events.top());
        Generator->Events.pop();

        if (evt->Type == Event::CallRequisition)
            {
            implement_call(evt);
            }
        else if (evt->Type == Event::CallEnding)
            {
            drop_call(evt);
            }
        }

    hasSimulated = true;
}
