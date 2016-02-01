#include <RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SQP_NetworkSimulation.h>
#include <Calls.h>
#include <RWA/TransparentSegment.h>
#include <RWA/Route.h>
#include <RWA/RoutingWavelengthAssignment.h>
#include <RWA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <Structure/Topology.h>
#include <Structure/Link.h>

SQP_NetworkSimulation::SQP_NetworkSimulation(std::shared_ptr<CallGenerator>
        Generator, std::shared_ptr<RoutingWavelengthAssignment> RWA,
        unsigned long NumMaxCalls, SignalQualityPrediction *SQP) :
    NetworkSimulation(Generator, RWA, NumMaxCalls), SQP(SQP)
{
    NodeUsage = std::vector<long int>(RWA->T->Nodes.size() + 1, 0);
}

void SQP_NetworkSimulation::implement_call(std::shared_ptr<Event> evt)
{
    NetworkSimulation::implement_call(evt);

    auto Links = RWA->R_Alg->route(evt->Parent);
    if (Links.empty())
        {
        return;
        }

    int LNMax = 1;
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

    std::vector<bool> sqp_LNMax(Links.size() + 1, false);
    for (unsigned numNode = 0; numNode <= Links.size(); ++numNode)
        {
        if ((numNode % LNMax == 0) ||
                ((numNode - 1) % LNMax == 0) ||
                ((numNode + 1) % LNMax == 0))
            {
            sqp_LNMax[numNode] = true;
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
