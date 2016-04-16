#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <boost/assign.hpp>
#include <iostream>
#include <fstream>
#include <RMSA/RoutingAlgorithms.h>
#include <Structure.h>
#include <Calls/Call.h>

using namespace RMSA::ROUT;

RoutingAlgorithm::RoutAlgNameBimap RoutingAlgorithm::RoutingAlgorithmNames =
    boost::assign::list_of<RoutingAlgorithm::RoutAlgNameBimap::relation>
#define X(a,b,c,d) (a,b)
    ROUTING_ALGORITHM
#undef X
    ;

RoutingAlgorithm::RoutAlgNicknameBimap
RoutingAlgorithm::RoutingAlgorithmNicknames =
    boost::assign::list_of<RoutingAlgorithm::RoutAlgNicknameBimap::relation>
#define X(a,b,c,d) (a,c)
    ROUTING_ALGORITHM
#undef X
    ;

RoutingAlgorithm::RoutingAlgorithm(std::shared_ptr<Topology> T,
                                   RoutingAlgorithms RoutAlgType) :
    RoutAlgType(RoutAlgType), T(T)
{

}

RoutingAlgorithm::RoutingAlgorithms
RoutingAlgorithm::define_RoutingAlgorithm()
{
    std::cout << std::endl << "-> Choose a routing algorithm." << std::endl;

    do
        {
        for (auto &routing : RoutingAlgorithmNames.left)
            {
            std::cout << "(" << routing.first << ")\t" << routing.second << std::endl;
            }

        int Routing_Alg;
        std::cin >> Routing_Alg;

        if (std::cin.fail() || RoutingAlgorithmNames.left.count
                ((RoutingAlgorithms) Routing_Alg) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid routing algorithm." << std::endl;
            std::cout << std::endl << "-> Choose a routing algorithm." << std::endl;
            }
        else
            {
            return (RoutingAlgorithms) Routing_Alg;
            }
        }
    while (1);

    return (RoutingAlgorithms) - 1;
}

std::shared_ptr<RoutingAlgorithm> RoutingAlgorithm::create_RoutingAlgorithm(
    RoutingAlgorithms Algorithm, std::shared_ptr<Topology> T)
{
    std::shared_ptr<RoutingAlgorithm> R_Alg;

    switch (Algorithm)
        {
#define X(a,b,c,d) case a: R_Alg = std::make_shared<d>(T); break;
            ROUTING_ALGORITHM
#undef X
        }

    R_Alg->load();
    return R_Alg;
}

std::vector<std::vector<std::weak_ptr<Link>>>
RoutingAlgorithm::route(std::shared_ptr<Call> C)
{
    return yen(C);
}

void RoutingAlgorithm::save(std::string SimConfigFileName)
{
    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << std::endl << "  [algorithms]" << std::endl << std::endl;
    SimConfigFile << "  RoutingAlgorithm = " << RoutingAlgorithmNicknames.left.at(
                      RoutAlgType)
                  << std::endl;
}

std::vector<std::vector<std::weak_ptr<Link>>> RoutingAlgorithm::dijkstra(
    std::shared_ptr<Call> C)
{
    /** Attention: this code breaks if there are nodes in the Topology with the
     * same ID. This should not happen. The nodes must have sequential ID. **/

    std::vector<double> MinDistance(T->Nodes.size() + 1,
                                    std::numeric_limits<double>::max());
    std::set<std::pair<int, std::shared_ptr<Node>>> ActiveVertices;
    std::vector<int> Precedent(T->Nodes.size() + 1, -1);

    MinDistance[C->Origin.lock()->ID] = 0;
    ActiveVertices.insert({0, C->Origin.lock()});

    unsigned int NumVisitedNodes = 0;

    while (!ActiveVertices.empty())
        {
        std::shared_ptr<Node> CurrentNode = ActiveVertices.begin()->second;

        if (CurrentNode == C->Destination.lock())
            {
            break;
            }

        if (NumVisitedNodes++ > T->Nodes.size()) //Found a negative loop
            {
            break;
            }

        ActiveVertices.erase(ActiveVertices.begin());

        for (auto &node : CurrentNode->Neighbours)
            {
            if (!node.lock()->is_NodeActive())
                {
                continue;
                }

            auto locknode = node.lock();
            double newLength = MinDistance[CurrentNode->ID] +
                               get_Cost(T->Links.at(std::make_pair(CurrentNode->ID, locknode->ID)), C);

            if (MinDistance[locknode->ID] > newLength)
                {
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

    if (Precedent[CurrentNode] == -1)
        {
        RouteLinks.clear();
        return {RouteLinks};
        }

    while (Precedent[CurrentNode] != -1)
        {
        NodesInRoute.push_back(Precedent[CurrentNode]);

            {
            int CurNode = Precedent[CurrentNode];
            Precedent[CurrentNode] = -1;
            CurrentNode = CurNode;
            } //Avoiding negative cost loops

        if (CurrentNode == -1)
            {
            RouteLinks.clear(); //Could not find route. Returns empty vector.
            return {RouteLinks};
            }
        }

    for (int i = NodesInRoute.size() - 1; i > 0; i--)
        {
        RouteLinks.push_back(T->Links.at(std::make_pair(NodesInRoute[i],
                                         NodesInRoute[i - 1])));
        }

    //Checks whether the route is correct
    //Usually it just isn't when there's a negative cost loop.
    if ((RouteLinks.front().lock()->Origin.lock()->ID != C->Origin.lock()->ID) ||
            (RouteLinks.back().lock()->Destination.lock()->ID != C->Destination.lock()->ID))
        {
        RouteLinks.clear();
        }

    return {RouteLinks};
}

std::vector<std::vector<std::weak_ptr<Link>>>
RoutingAlgorithm::yen(std::shared_ptr<Call> C)
{
    std::vector<std::vector<std::weak_ptr<Link>>> RouteLinks;
    RouteLinks.push_back(dijkstra(C).back());

    std::clog << "Rota 1: " << std::endl;
    for (auto &link : RouteLinks.back())
        {
        std::clog << *(link.lock()) << std::endl;
        }

    while (RouteLinks.size() < kShortestPaths)
        {
        bool foundRoute = false;

        auto lastShortRoute = RouteLinks.back();
        auto currShortestRoute = RouteLinks.back();
        double minRouteCost = std::numeric_limits<double>::max();

        for (unsigned n = 0; n < lastShortRoute.size(); ++n)
            {
            auto spurNode = lastShortRoute.at(n).lock()->Origin;
            auto rootPath = std::vector<std::weak_ptr<Link>>(lastShortRoute.begin(),
                            lastShortRoute.begin() + n);

            std::vector<std::weak_ptr<Node>> deactivatedNodes;
            std::vector<std::weak_ptr<Link>> deactivatedLinks;

            //Deactives some nodes and links
            for (auto &link : rootPath)
                {
                link.lock()->Origin.lock()->set_NodeInactive();
                deactivatedNodes.push_back(link.lock()->Origin);
                }
            for (auto &previousRoutes : RouteLinks)
                {
                if (previousRoutes.size() < n)
                    {
                    continue;
                    }

                bool shareRoot = true;
                for (unsigned link = 0; (link < n) && shareRoot; ++link)
                    {
                    shareRoot &= (rootPath[link].lock() == previousRoutes[link].lock());
                    }
                if (shareRoot)
                    {
                    previousRoutes[n].lock()->set_LinkInactive();
                    deactivatedLinks.push_back(previousRoutes[n]);
                    }
                }

            auto dummyC = std::make_shared<Call>(spurNode, C->Destination, C->Bitrate);
            auto alternativeRoute = dijkstra(dummyC).front();

            if (!alternativeRoute.empty())
                {
                foundRoute = true;
                auto testRoute = rootPath;
                testRoute.insert(testRoute.end(), alternativeRoute.begin(),
                                 alternativeRoute.end());
                double routeCost = get_RoutingCost(testRoute, C);
                if (routeCost < minRouteCost)
                    {
                    minRouteCost = routeCost;
                    currShortestRoute = testRoute;
                    }
                }

            //Reactivates nodes and links
            for (auto &node : deactivatedNodes)
                {
                node.lock()->set_NodeActive();
                }
            for (auto &link : deactivatedLinks)
                {
                link.lock()->set_LinkActive();
                }

            }
        if (!foundRoute)
            {
            break;
            }
        RouteLinks.push_back(currShortestRoute);
        std::clog << "Rota " << RouteLinks.size() << ": " << std::endl;
        for (auto &link : RouteLinks.back())
            {
            std::clog << *(link.lock()) << std::endl;
            }
        }

    return RouteLinks;
}

double RoutingAlgorithm::get_RoutingCost(std::vector<std::weak_ptr<Link>> links,
        std::shared_ptr<Call> C)
{
    double cost = 0;

    for (auto &link : links)
        {
        cost += get_Cost(link, C);
        }

    return cost;
}
