#include <RWA/RoutingAlgorithms/DijkstraRoutingAlgorithm.h>
#include <Calls/Call.h>
#include <Structure/Node.h>
#include <Structure/Link.h>
#include <Structure/Topology.h>
#include <algorithm>
#include <limits>
#include <map>
#include <set>

DijkstraRoutingAlgorithm::DijkstraRoutingAlgorithm(std::shared_ptr<Topology> T)
    : RoutingAlgorithm(T) {

}

std::vector<std::weak_ptr<Link>> DijkstraRoutingAlgorithm::route(
std::shared_ptr<Call> C) {
    /** Attention: this code breaks if there are nodes in the Topology with the
     * same ID. This should not happen. The nodes must have sequential ID. **/

    std::vector<double> MinDistance(T->Nodes.size() + 1,
                                         std::numeric_limits<double>::max());
    std::set<std::pair<int, std::shared_ptr<Node>>> ActiveVertices;
    std::vector<int> Precedent(T->Nodes.size() + 1, -1);

    MinDistance[C->Origin.lock()->ID] = 0;
    ActiveVertices.insert({0, C->Origin.lock()});

    unsigned int NumVisitedNodes = 0;

    while (!ActiveVertices.empty()) {
        std::shared_ptr<Node> CurrentNode = ActiveVertices.begin()->second;

        if (CurrentNode == C->Destination.lock()) {
            break;
        }

        if (NumVisitedNodes++ > T->Nodes.size()) { //Found a negative loop
            break;
        }

        ActiveVertices.erase(ActiveVertices.begin());

        for (auto &node : CurrentNode->Neighbours) {
            auto locknode = node.lock();
            double newLength = MinDistance[CurrentNode->ID] +
                                    get_Cost(T->Links.at(OrigDestPair(CurrentNode->ID, locknode->ID)), C);

            if (MinDistance[locknode->ID] > newLength) {
                ActiveVertices.erase({MinDistance[locknode->ID], locknode});
                MinDistance[locknode->ID] = newLength;
                ActiveVertices.insert({newLength, locknode});
                Precedent[locknode->ID] = CurrentNode->ID;
            }
        }
    }

    std::vector<int> NodesInRoute;
    std::vector<std::weak_ptr<Link>> RouteLinks;

    int CurrentNode = C->Destination.lock()->ID;
    NodesInRoute.push_back(CurrentNode);

    while (Precedent[CurrentNode] != -1) {
        NodesInRoute.push_back(Precedent[CurrentNode]);

        {
            int CurNode = Precedent[CurrentNode];
            Precedent[CurrentNode] = -1;
            CurrentNode = CurNode;
        } //Avoiding negative cost loops

        if (CurrentNode == -1 || NumVisitedNodes > T->Nodes.size()) {
            RouteLinks.clear(); //Could not find route. Returns empty vector.
            return RouteLinks;
        }
    }

    for (int i = NodesInRoute.size() - 1; i > 0; i--) {
        RouteLinks.push_back(T->Links.at(OrigDestPair(NodesInRoute[i],
                                         NodesInRoute[i - 1])));
    }

    return RouteLinks;
}
