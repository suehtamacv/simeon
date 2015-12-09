#include <algorithm>
#include <boost/assert.hpp>
#include <RWA/Route.h>
#include <Structure/Slot.h>
#include <Structure/Node.h>
#include <Structure/Link.h>

Route::Route(std::vector<TransparentSegment> Segments,
             std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>, std::owner_less<std::weak_ptr<Link>>>
             Slots) : Segments(Segments), Slots(Slots) {
    for (auto segment : Segments) {
        for (auto node : segment.Nodes) {
            if (node.lock() != segment.Nodes.back().lock()) {
                Nodes.push_back(node);
            }

            Regenerators.emplace(node, 0);
        }

        Regenerators[segment.Nodes.back()] = segment.NumRegUsed;

        for (auto link : segment.Links) {
            Links.push_back(link);
        }
    }

    Nodes.push_back(Segments.back().Nodes.back());
    Regenerators.emplace(Segments.back().Nodes.back(), 0);
}

Signal Route::bypass(Signal S) {
    //Does not consider regeneration
    for (auto segment : Segments) {
        S = segment.bypass(S);
    }

    return S;
}

Signal Route::partial_bypass(Signal S, std::weak_ptr<Node> orig,
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
