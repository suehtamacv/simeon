#include <RWA/Routing/DijkstraRoutingAlgorithm.h>
#include <limits>
#include <map>

DijkstraRoutingAlgorithm::DijkstraRoutingAlgorithm(std::shared_ptr<Topology> T)
    : RoutingAlgorithm(T) {

}

std::vector<std::weak_ptr<Link>> DijkstraRoutingAlgorithm::route(Call C) {
    /** Attention: this code breaks if there are nodes in the Topology with the
     * same ID. This should not happen. **/

    std::map<int, long double> VertexCost;
    std::map<int, int> Precedent;
    std::vector<std::shared_ptr<Node>> UnvisitedNodes;
    std::vector<int> NodesInRoute;
    std::vector<std::weak_ptr<Link>> RouteLinks;

    for (auto it = T->Nodes.begin(); it != T->Nodes.end(); ++it) {
        VertexCost.emplace((*it)->ID, std::numeric_limits<double>::max());
        Precedent.emplace((*it)->ID, -1);
        UnvisitedNodes.push_back(*it);
    }

    VertexCost[ C.Origin.lock()->ID ] = 0;

    while (!UnvisitedNodes.empty()) {
        std::shared_ptr<Node> CurrentNode = UnvisitedNodes[0];

        for (auto it = UnvisitedNodes.begin(); it != UnvisitedNodes.end(); ++it) {
            if (VertexCost[CurrentNode->ID] < VertexCost[(*it)->ID]) {
                CurrentNode.reset();
                CurrentNode = *it;
            }
        }

        if (CurrentNode == C.Destination.lock()) {
            break;
        }

        for (auto it = UnvisitedNodes.begin(); it != UnvisitedNodes.end(); ++it) {
            if (CurrentNode == *it) {
                UnvisitedNodes.erase(it);
                break;
            }
        }

        for (auto it = CurrentNode->Neighbours.begin();
                it != CurrentNode->Neighbours.end(); ++it) {
            long double AltCost = VertexCost[CurrentNode->ID] +
                                  get_Cost(T->Links.at(OrigDestPair(CurrentNode->ID, (*it).lock()->ID)), C);

            if (AltCost < VertexCost[(*it).lock()->ID]) {
                VertexCost[(*it).lock()->ID] = AltCost;
                Precedent[(*it).lock()->ID] = CurrentNode->ID;
            }
        }
    }

    unsigned int CurrentNode = C.Destination.lock()->ID;
    NodesInRoute.push_back(CurrentNode);

    while (Precedent[CurrentNode] != -1) {
        NodesInRoute.push_back(Precedent[CurrentNode]);
        CurrentNode = Precedent[CurrentNode];
    }

    for (int i = NodesInRoute.size(); i != 1; i--) {
        RouteLinks.insert(RouteLinks.begin(), T->Links.at(
                              OrigDestPair(NodesInRoute[i], NodesInRoute[i - 1])));
    }

    return RouteLinks;
}
