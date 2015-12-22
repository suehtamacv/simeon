#ifndef NETWORKSIMULATION_H
#define NETWORKSIMULATION_H

#include <memory>
#include <Calls/CallGenerator.h>
#include <RWA/RoutingWavelengthAssignment.h>

class NetworkSimulation {
  public:
    NetworkSimulation(std::shared_ptr<CallGenerator> Generator,
                      std::shared_ptr<RoutingWavelengthAssignment> RWA,
                      long unsigned NumMaxCalls);

    void run();
    void print();

    std::shared_ptr<CallGenerator> Generator;
    std::shared_ptr<RoutingWavelengthAssignment> RWA;

    long unsigned NumMaxCalls;
    long unsigned NumCalls;
    long unsigned NumBlockedCalls;

    long double get_CallBlockingProbability();
    long double get_Load();

    bool hasSimulated;

  private:
    void implement_call(std::shared_ptr<Event> evt);
    void drop_call(std::shared_ptr<Event> evt);
};

#endif // NETWORKSIMULATION_H
