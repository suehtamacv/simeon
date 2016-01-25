#include <RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SQP_NetworkSimulation.h>
#include <Calls.h>
#include <RWA/TransparentSegment.h>
#include <RWA/Route.h>
#include <RWA/RoutingWavelengthAssignment.h>
#include <Structure/Topology.h>

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

    if (evt->Parent->Status == Call::Blocked)
        {
        return;
        }

    for (auto &segment : evt->route->Segments)
        {
        auto LNMax = SQP->get_LNMax(evt->Parent->Bitrate, segment.ModScheme);
        std::vector<bool> sqp_LNMax(segment.Nodes.size(), false);

        for (unsigned numNode = 0; numNode < segment.Nodes.size(); ++numNode)
            {
            if ((numNode % LNMax == 0) ||
                    ((numNode - 1) % LNMax == 0) ||
                    ((numNode + 1) % LNMax == 0))
                {
                sqp_LNMax[numNode] = true;
                }
            }

        for (unsigned numNode = 0; numNode < segment.Nodes.size(); ++numNode)
            {
            if (sqp_LNMax[numNode])
                {
                NodeUsage[segment.Nodes[numNode].lock()->ID]++;
                }
            }
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
