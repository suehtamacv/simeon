#include <RWA/Route.h>
#include <Structure/Slot.h>
#include <Structure/Node.h>
#include <Structure/Link.h>

Route::Route(std::vector<std::weak_ptr<Link> > Links,
             std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot> > > Slots)
    : Links(Links), Slots(Slots) {

    for (auto it = Links.begin(); it != Links.end(); ++it) {
        if (it == Links.begin()) {
            Nodes.push_back((*it).lock()->Origin);
        }

        Nodes.push_back((*it).lock()->Destination);
    }

}

Signal Route::bypass() {
    Signal S;

    for (auto it = Links.begin(); it != Links.end(); ++it) {
        if (it == Links.begin()) {
            S = (*it).lock()->Origin.lock()->add(S);
        }

        S = (*it).lock()->bypass(S);

        if ((*it).lock() == Links.back().lock()) {
            S = (*it).lock()->Destination.lock()->drop(S);
        }
    }

    return S;
}
