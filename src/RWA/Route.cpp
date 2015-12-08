#include <algorithm>
#include <boost/assert.hpp>
#include <RWA/Route.h>
#include <Structure/Slot.h>
#include <Structure/Node.h>
#include <Structure/Link.h>

Route::Route(std::vector<std::weak_ptr<Link> > Links,
             std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot> > > Slots)
    : Links(Links), Slots(Slots) {

    for (auto it : Links) {
        if (it.lock() == Links.front().lock()) {
            Nodes.push_back(it.lock()->Origin);
            Regenerators.emplace(it.lock()->Origin, 0);
        }

        Nodes.push_back(it.lock()->Destination);
        Regenerators.emplace(it.lock()->Destination, 0);
    }

}

Signal Route::bypass() {
    Signal S;

    for (auto it : Links) {
        if (it.lock() == Links.front().lock()) {
            S = it.lock()->Origin.lock()->add(S);
        }

        S = it.lock()->bypass(S);

        if (it.lock() == Links.back().lock()) {
            S = it.lock()->Destination.lock()->drop(S);
        }
    }

    return S;
}

Signal Route::partial_bypass(std::weak_ptr<Node> orig,
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

    Signal S;

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

unsigned int Route::get_MaxContigSlots(std::weak_ptr<Node> orig,
                                       std::weak_ptr<Node> dest) {

    auto currentLink = Links.begin();

    while ((*currentLink).lock()->Origin.lock() != orig.lock()) {
        currentLink++;
    }

    std::vector<bool> SlotsAvailability;

    for (unsigned int i = 0; i < Link::NumSlots; i++) {
        SlotsAvailability.push_back((*currentLink).lock()->isSlotFree(i));
    }

    while ((*currentLink).lock()->Origin.lock() != dest.lock()) {
        for (unsigned int i = 0; i < Link::NumSlots; i++) {
            SlotsAvailability[i] = SlotsAvailability[i] &&
                                   (*currentLink).lock()->isSlotFree(i);
        }

        currentLink++;
    }

    unsigned MaxSlots = 0;
    unsigned CurrentFreeSlots = 0;

    for (auto slot : SlotsAvailability) {
        if (slot) {
            CurrentFreeSlots++;
        } else {
            CurrentFreeSlots = 0;
        }

        if (CurrentFreeSlots > MaxSlots) {
            MaxSlots = CurrentFreeSlots;
        }
    }

    return MaxSlots;
}
