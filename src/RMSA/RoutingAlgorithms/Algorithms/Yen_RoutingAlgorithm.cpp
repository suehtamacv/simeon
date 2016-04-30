#include "include/RMSA/RoutingAlgorithms/Algorithms/Yen_RoutingAlgorithm.h"
#include "include/Structure/Node.h"
#include "include/Structure/Link.h"
#include "include/Structure/Topology.h"
#include "Calls/Call.h"
#include <iostream>

using namespace RMSA::ROUT;
unsigned int Yen_RoutingAlgorithm::kShortestPaths = 1;
bool Yen_RoutingAlgorithm::hasLoaded = false;

Yen_RoutingAlgorithm::Yen_RoutingAlgorithm(std::shared_ptr<Topology> T,
        RoutingCost::RoutingCosts Cost, bool runLoad) :
    RoutingAlgorithm(T, yen, Cost, runLoad)
{
    Dijkstra = create_RoutingAlgorithm(dijkstra, Cost, T);
}

void Yen_RoutingAlgorithm::load()
{
    if (hasLoaded)
        {
        return;
        }
    hasLoaded = true;

    std::cout << std::endl << "-> Define the number k of paths to Yen algorithm."
              << std::endl;

    do
        {
        std::cin >> kShortestPaths;

        if (std::cin.fail() || kShortestPaths <= 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of paths." << std::endl;
            std::cout << std::endl << "-> Define the number k of paths to Yen algorithm."
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);
}

void Yen_RoutingAlgorithm::save(std::string name)
{
    RoutingAlgorithm::save(name);
}

std::vector<std::vector<std::weak_ptr<Link>>>
Yen_RoutingAlgorithm::route(std::shared_ptr<Call> C)
{
    if (!hasLoaded)
        {
        load();
        }

    std::vector<std::vector<std::weak_ptr<Link>>> RouteLinks;
    RouteLinks.push_back(Dijkstra->route(C).back());

    while (RouteLinks.size() < kShortestPaths)
        {
        bool foundRoute = false;

        auto lastShortRoute = RouteLinks.back();
        auto currShortestRoute = RouteLinks.back();
        double minRouteCost = std::numeric_limits<double>::max();

        for (unsigned n = 0; n < lastShortRoute.size(); ++n)
            {
            auto spurNode = lastShortRoute[n].lock()->Origin;
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
            auto alternativeRoute = Dijkstra->route(dummyC).front();

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
        }

    return RouteLinks;
}
