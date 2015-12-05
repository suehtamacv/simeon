#include <RWA/Route.h>
#include <Structure/Slot.h>
#include <Structure/Node.h>
#include <Structure/Link.h>

Route::Route(std::vector<std::weak_ptr<Link>> Links,
             std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>> Slots)
    : Links(Links), Slots(Slots) {

    for (auto it = Links.begin(); it != Links.end(); ++it) {
        if (it == Links.begin()) {
            Nodes.push_back((*it).lock()->Origin);
        }

        Nodes.push_back((*it).lock()->Destination);
    }

}

