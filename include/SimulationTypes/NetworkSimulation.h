#ifndef NETWORKSIMULATION_H
#define NETWORKSIMULATION_H

#include <memory>
#include <fstream>

class CallGenerator;
class Event;

namespace RMSA
{
class RoutingWavelengthAssignment;
}

namespace Simulations
{

/**
 * @brief The NetworkSimulation class is the a basic block. This class runs a
 * network simulation, coordinating the CallGenerator and the RoutingWavelengthAssignment
 * objects.
 */
class NetworkSimulation
{
public:
    /**
     * @brief NetworkSimulation is the default constructor of a network simulation.
     * @param Generator is a pointer to a call generator object.
     * @param RMSA is a pointer to a RoutingWavelengthAssignment object.
     * @param NumMaxCalls is the number of call requests that will be simulated.
     */
    NetworkSimulation(std::shared_ptr<CallGenerator> Generator,
                      std::shared_ptr<RMSA::RoutingWavelengthAssignment> RMSA,
                      long unsigned NumMaxCalls);

    /**
     * @brief run silently runs a network simulation.
     */
    void run();
    /**
     * @brief print runs a network simulation and prints its result (in terms of
     * call request blocking probability).
     */
    void print();

    /**
     * @brief Generator is a pointer to this simulation's call generator.
     */
    std::shared_ptr<CallGenerator> Generator;
    /**
     * @brief RMSA is a pointer to this simulation's RMSA object.
     */
    std::shared_ptr<RMSA::RoutingWavelengthAssignment> RMSA;

    /**
     * @brief NumMaxCalls is the number of call requests that will be simulated.
     */
    long unsigned NumMaxCalls;

    /**
     * @brief NumCalls is the number of call requests that have been simulated.
     */
    long unsigned NumCalls;
    /**
     * @brief NumBlockedCalls is the number of blocked call requests.
     */
    long unsigned NumBlockedCalls;
    /**
     * @brief NumBlockedCalls_Spectrum is the number of calls requests that have been
     * blocked due to not enough spectrum available.
     */
    long unsigned NumBlockedCalls_Spectrum;
    /**
     * @brief NumBlockedCalls_ASE_Noise is the number of call requests that have been
     * blocked due to an OSNR too low.
     */
    long unsigned NumBlockedCalls_ASE_Noise;
    /**
     * @brief NumBlockedCalls_FilterImperfection is the number of call requests that
     * have been blocked due to too little power on the required spectrum slice.
     */
    long unsigned NumBlockedCalls_FilterImperfection;

    /**
     * @brief get_CallBlockingProbability returns a estimation of the call request
     * blocking probability.
     * @return a estimation of the call request blocking probability.
     */
    double get_CallBlockingProbability();
    /**
     * @brief get_Load returns the load of this simulation, in Erlangs.
     * @return the load of this simulation, in Erlangs.
     */
    double get_Load();

    /**
     * @brief hasSimulated is true iff the simulation has already run.
     */
    bool hasSimulated;

protected:
    void implement_call(std::shared_ptr<Event> evt);
    void drop_call(std::shared_ptr<Event> evt);
};
}

#endif // NETWORKSIMULATION_H
