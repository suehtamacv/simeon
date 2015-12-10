#ifndef NETWORKSIMULATION_H
#define NETWORKSIMULATION_H

#include <memory>
#include <Calls/CallGenerator.h>
#include <RWA/RoutingWavelengthAssignment.h>

class NetworkSimulation {
  public:
    NetworkSimulation(std::shared_ptr<CallGenerator> Generator,
                      std::shared_ptr<RoutingWavelengthAssignment> RWA,
                      long unsigned NumCalls);

    void run();

    std::shared_ptr<CallGenerator> Generator;
    std::shared_ptr<RoutingWavelengthAssignment> RWA;
    long unsigned NumCalls;
};

#endif // NETWORKSIMULATION_H
