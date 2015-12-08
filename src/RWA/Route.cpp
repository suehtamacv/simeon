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
