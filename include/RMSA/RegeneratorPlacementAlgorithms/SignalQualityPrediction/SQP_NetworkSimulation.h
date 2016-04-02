#ifndef SQP_NETWORKSIMULATION_H
#define SQP_NETWORKSIMULATION_H

#include <SimulationTypes/NetworkSimulation.h>
#include "SignalQualityPrediction.h"

class SQP_NetworkSimulation : public Simulations::NetworkSimulation
{
    friend class SignalQualityPrediction;
public:
    SQP_NetworkSimulation(std::shared_ptr<CallGenerator> Generator,
                          std::shared_ptr<RoutingWavelengthAssignment> RMSA,
                          long unsigned NumMaxCalls,
                          SignalQualityPrediction *SQP);

    void run();

private:
    SignalQualityPrediction *SQP;
    void implement_call(std::shared_ptr<Event> evt);

    std::vector<long int> NodeUsage;
};

#endif // SQP_NETWORKSIMULATION_H
