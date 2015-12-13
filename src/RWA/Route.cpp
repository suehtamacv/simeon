#include <algorithm>
#include <boost/assert.hpp>
#include <RWA/Route.h>
#include <Structure/Slot.h>
#include <Structure/Node.h>
#include <Structure/Link.h>

Route::Route(std::vector<TransparentSegment> Segments,
             std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>, std::owner_less<std::weak_ptr<Link>>>
             Slots) : Segments(Segments), Slots(Slots) {
    Nodes.clear();
    Links.clear();
    Slots.clear();
    Regenerators.clear();

    for (auto segment : Segments) {
        Nodes.insert(Nodes.end(), segment.Nodes.begin(), segment.Nodes.end() - 1);
        BOOST_ASSERT_MSG((!segment.NumRegUsed) ||
                         (segment.Nodes.back().lock()->get_NodeType() != Node::TransparentNode),
                         "Trying to regenerate in transparent node.");
        Regenerators[segment.Nodes.back()] = segment.NumRegUsed;

        Links.insert(Links.end(), segment.Links.begin(), segment.Links.end());
    }

    if (!Segments.empty()) {
        Nodes.push_back(Segments.back().Nodes.back());
    }
}

Route::Route(const Route &route) {
    for (auto segment : route.Segments) {
        Segments.push_back(segment);
    }

    for (auto node : route.Nodes) {
        Nodes.push_back(node);
    }

    for (auto link : route.Links) {
        Links.push_back(link);
    }

    for (auto node : route.Regenerators) {
        Regenerators.emplace(node.first, node.second);
    }

    for (auto link : route.Slots) {
        Slots.emplace(link.first, link.second);
    }
}

Signal &Route::bypass(Signal &S) {
    return Segments.back().bypass(S);
}

Signal &Route::partial_bypass(Signal &S, std::weak_ptr<Node> orig,
                              std::weak_ptr<Node> dest) {

    auto currentNode = Nodes.begin();

    for (auto node = Nodes.begin(); node != Nodes.end(); ++node) {
        BOOST_ASSERT_MSG((*node).lock() != Nodes.end()->lock(),
                         "orig node is not in the Route.");

        if (orig.lock() == (*node).lock()) {
            currentNode = node;
            break;
        }
    }

    for (auto node = currentNode ; node != Nodes.end(); ++node) {
        BOOST_ASSERT_MSG((*node).lock() != Nodes.end()->lock(),
                         "dest node is not in the Route.");

        if (dest.lock() == (*node).lock()) {
            break;
        }
    }

    auto currentLink = Links.begin();

    while ((*currentLink).lock()->Origin.lock() != orig.lock()) {
        currentLink++;
    }

    //Traverses the network
    do {
        if ((*currentNode).lock() == orig.lock()) {
            S = orig.lock()->add(S);
        } else if ((*currentNode).lock() == dest.lock()) {
            S = dest.lock()->drop(S);
            break;
        } else {
            S = (*currentNode).lock()->bypass(S);
        }

        currentNode++;

        S = (*currentLink).lock()->bypass(S);

        currentLink++;
    } while (currentNode != Nodes.end());

    return S;
}
