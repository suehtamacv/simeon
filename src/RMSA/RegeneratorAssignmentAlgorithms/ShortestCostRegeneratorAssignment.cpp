#include "include/RMSA/RegeneratorAssignmentAlgorithms/ShortestCostRegeneratorAssignment.h"
#include "RMSA/TransparentSegment.h"
#include "Structure/Link.h"
#include "Structure/Node.h"
#include "Calls/Call.h"

using namespace RMSA::RA;

ShortestCostRegeneratorAssignment::ShortestCostRegeneratorAssignment(
    std::shared_ptr<Topology> T,
    std::set<ModulationScheme> Schemes) :
    RegeneratorAssignmentAlgorithm(T, SCRA, Schemes)
{

}

std::vector<RMSA::TransparentSegment>
ShortestCostRegeneratorAssignment::assignRegenerators
(std::shared_ptr<Call> C,
 std::vector<std::weak_ptr<Link>> Links)
{
    std::vector<RMSA::TransparentSegment> Segments;
    unsigned int numReqRegenerators = get_NumNeededRegenerators(C);

    std::vector<std::weak_ptr<Node>> Nodes;
    for (auto &link : Links)
        {
        Nodes.push_back(link.lock()->Origin);
        }
    Nodes.push_back(Links.back().lock()->Destination);

    std::set<std::pair<unsigned int, unsigned int>> possibleJumps;
    std::vector<int> possibleNodes;

    for (unsigned curNode = 0; curNode < Nodes.size(); ++curNode)
        {
        //Segment can only start on the first node or on an translucent node.
        if ((curNode != 0) && (curNode != Nodes.size() - 1) &&
                (Nodes[curNode].lock()->get_NumAvailableRegenerators() == 0))
            {
            continue;
            }
        possibleNodes.push_back(curNode);

        for (unsigned jump = Nodes.size() - 1; jump > curNode; --jump)
            {
            if (((jump == (Nodes.size() - 1)) ||
                    Nodes[jump].lock()->get_NumAvailableRegenerators() >= numReqRegenerators) &&
                    (isThereSpectrumAndOSNR(C, Links, Nodes[curNode], Nodes[jump])))
                {
                possibleJumps.insert({curNode, jump});
                }
            }
        }

    std::map<int, double> nodeCosts;
    std::map<int, int> Precedent;
    for (auto &node : possibleNodes)
        {
        nodeCosts.insert({node, std::numeric_limits<double>::max()});
        Precedent.insert({node, -1});
        }
    nodeCosts[0] = 0;

    for (auto &possibleJump : possibleJumps)
        {
        int numReg = (possibleJump.second != Nodes.size() - 1) ? numReqRegenerators : 0;
        double cost = get_Cost(createTransparentSegment(C, Links,
                               Nodes[possibleJump.first], Nodes[possibleJump.second], numReg), Nodes, C);

        if (nodeCosts[possibleJump.first] + cost < nodeCosts[possibleJump.second])
            {
            nodeCosts[possibleJump.second] = nodeCosts[possibleJump.first] + cost;
            Precedent[possibleJump.second] = possibleJump.first;
            }
        }

    unsigned CurrentNode = Nodes.size() - 1;
    while (Precedent[CurrentNode] != -1)
        {
        int numReg = (CurrentNode != Nodes.size() - 1) ? numReqRegenerators : 0;
        Segments.push_back(createTransparentSegment(C, Links,
                           Nodes[Precedent[CurrentNode]],
                           Nodes[CurrentNode], numReg));
        CurrentNode = Precedent[CurrentNode];
        }

    if (CurrentNode != 0)
        {
        Segments.clear();
        return Segments;
        }

    std::reverse(Segments.begin(), Segments.end());
    return Segments;
}

void ShortestCostRegeneratorAssignment::save(std::string filename)
{
    RegeneratorAssignmentAlgorithm::save(filename);
}

double ShortestCostRegeneratorAssignment::get_Cost(const TransparentSegment
        &segment, std::vector<std::weak_ptr<Node>> Nodes, std::shared_ptr<Call> C)
{
    double cost = 0;

    cost += -0.10; //DC Level

        {
        //Normalized number of required slots
        int NumSlots = segment.Links.size() *
                       segment.ModScheme.get_NumSlots(C->Bitrate);
        int maxNumSlots = (Nodes.size() - 1) *
                          (*ModulationSchemes.begin()).get_NumSlots(C->Bitrate);
        cost += NumSlots / (double) maxNumSlots;
        }

        {
        //Normalized number of required regenerators
        if (segment.NumRegUsed)
            {
            cost += segment.NumRegUsed /
                    (double) segment.Nodes.back().lock()->get_NumAvailableRegenerators();
            }
        }

    return cost;
}
