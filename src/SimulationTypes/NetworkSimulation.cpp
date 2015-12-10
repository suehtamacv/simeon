#include <boost/assert.hpp>
#include <SimulationTypes/NetworkSimulation.h>
#include <Structure/Slot.h>
#include <RWA/Route.h>

NetworkSimulation::NetworkSimulation(std::shared_ptr<CallGenerator> Generator,
                                     std::shared_ptr<RoutingWavelengthAssignment> RWA,
                                     unsigned long NumMaxCalls) :
    Generator(Generator), RWA(RWA), NumMaxCalls(NumMaxCalls) {
    NumCalls = 0;
    NumBlockedCalls = 0;
    hasSimulated = false;
}

void NetworkSimulation::run() {
    NumCalls++;
    Generator->generate_Call(); //Generates first call

    while (NumCalls < NumMaxCalls) {
        std::shared_ptr<Event> evt(Generator->Events.top());
        Generator->Events.pop();

        if (evt->Type == Event::CallRequisition) {
            implement_call(evt);
        } else if (evt->Type == Event::CallEnding) {
            drop_call(evt);
        }
    }

    hasSimulated = true;
}

void NetworkSimulation::implement_call(std::shared_ptr<Event> evt) {
    auto route = RWA->routeCall(evt->Parent);
    evt->Parent->CallEnding.lock()->route = route;

    BOOST_ASSERT_MSG(evt->Parent->Status != Call::Not_Evaluated,
                     "Call was neither accepted nor blocked.");

    if (evt->Parent->Status == Call::Blocked) {
        NumBlockedCalls++;
    } else {
        for (auto node : route->Slots) {
            for (auto slot : node.second) {
                slot.lock()->useSlot();
            }
        }
    }

    NumCalls++;
    Generator->generate_Call();
}

void NetworkSimulation::drop_call(std::shared_ptr<Event> evt) {
    if (evt->Parent->Status == Call::Implemented)
        for (auto node : evt->route->Slots) {
            for (auto slot : node.second) {
                slot.lock()->freeSlot();
            }
        }
}

long double NetworkSimulation::get_CallBlockingProbability() {
    if (!hasSimulated) {
        run();
    }

    return NumBlockedCalls / (1.0 * NumCalls);
}
