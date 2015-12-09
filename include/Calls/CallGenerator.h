#ifndef CALLGENERATOR_H
#define CALLGENERATOR_H

#include <memory>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <Calls/Event.h>
#include <GeneralClasses/TransmissionBitrate.h>
#include <Structure/Topology.h>
#include <queue>

/**
 * @brief The CallGenerator class implements methods to continuously generate
 * calls.
 *
 * Currently, the origin and destination node are chosen with an uniform
 * distribution and the call duration and arrival times are chosen with
 * exponential distributions, the former with parameter mu and the latter
 * with parameter 1/h.
 */
class CallGenerator {
  public:
    /**
     * @brief CallGenerator is the standard constructor for a CallGenerator.
     * @param NetTopology is the topology over which the calls are generated.
     * @param mu is the parameter for the call duration distribution.
     * @param h is the parameter for the call interarrival time distribution.
     */
    CallGenerator(std::shared_ptr<Topology> NetTopology, long double mu,
                  long double h);

    /**
     * @brief Events is a priority queue.
     *
     * The Events of the topology are stored here in increasing order of their
     * ocurring times.
     */
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> Events;

    /**
     * @brief NetTopology is the Topology over which the calls are generated.
     */
    std::shared_ptr<Topology> NetTopology;
    /**
     * @brief mu is the parameter for the call duration exponential distribution.
     */
    long double mu;
    /**
     * @brief h is t parameter for the cl interarrival time exponential
     * distribution.
     */
    long double h;
    /**
     * @brief simulationTime is the current time seen by the last call.
     */
    long double simulationTime;


    /**
     * @brief MersenneTwister is the Random Number Generator.
     */
    static boost::mt19937 MersenneTwister;

    //Distributions
    boost::uniform_int<> UniformDistribution;
    boost::exponential_distribution<> ExponentialDistributionMu;
    boost::exponential_distribution<> ExponentialDistributionH;

    //Number Generators
    std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::uniform_int<> >>
            UniformGenerator;
    std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >>
            ExponentialGeneratorMu;
    std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >>
            ExponentialGeneratorH;

    Call generate_Call(TransmissionBitrate Bitrate);
};

#endif // CALLGENERATOR_H
