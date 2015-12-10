#include <SimulationTypes/NetworkSimulation.h>
#include <Structure/Slot.h>
#include <RWA/Route.h>

NetworkSimulation::NetworkSimulation(std::shared_ptr<CallGenerator> Generator,
                                     std::shared_ptr<RoutingWavelengthAssignment> RWA,
                                     unsigned long NumMaxCalls) :
    Generator(Generator), RWA(RWA), NumMaxCalls(NumMaxCalls) {
    NumCalls = 0;
    NumBlockedCalls = 0;
}

void NetworkSimulation::run() {
    NumCalls++;
    Generator->generate_Call(); //Generates first call

    while (NumCalls < NumMaxCalls) {
        Event evt = Generator->Events.top();
        Generator->Events.pop();

        if (evt.Type == Event::CallRequisition) {
            implement_call(evt);
        } else if (evt.Type == Event::CallEnding) {
            drop_call(evt);
        }
    }
}

bool NetworkSimulation::implement_call(Event evt) {
    std::shared_ptr<Route> route = RWA->routeCall(*(evt.Parent));

    evt.Parent->CallEnding.route = route;

    if (route->Slots.empty()) {
        //Blocked Call
        NumBlockedCalls++;

        Generator->generate_Call();
        return false;
    } else {
        for (auto node : route->Slots) {
            for (auto slot : node.second) {
                slot.lock()->useSlot();
            }
        }

        Generator->generate_Call();

        return true;
    }
}

void NetworkSimulation::drop_call(Event evt) {
    if (!evt.route->Slots.empty())
        for (auto node : evt.route->Slots) {
            for (auto slot : node.second) {
                slot.lock()->freeSlot();
            }
        }
}
