#ifndef CALLGENERATOR_H
#define CALLGENERATOR_H

#include <memory>
#include <random>
#include <queue>
#include <Calls/Event.h>
#include <GeneralClasses/TransmissionBitrate.h>
#include <Structure/Topology.h>

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
  private:
    /**
     * @brief The EventCompare struct is used to compare two events. Associated
     * with the priority_queue, this comparison organizes the events in increasing
     * order of their occurral times.
     */
    struct EventCompare {
        bool operator()(const std::shared_ptr<Event> a,
                        const std::shared_ptr<Event> b) const {
            return *a > *b;
        }
    };

  public:
    /**
     * @brief CallGenerator is the standard constructor for a CallGenerator.
     * @param T is the topology over which the calls are generated.
     * @param h is the parameter for the call interarrival time distribution.
     * @param Bitrates is a vector with the possible transmission bitrates.
     */
    CallGenerator(std::shared_ptr<Topology> T, double h,
                  std::vector<TransmissionBitrate> Bitrates);

    /**
     * @brief Events is a priority queue.
     *
     * The Events of the topology are stored here in increasing order of their
     * ocurring times.
     */
    std::priority_queue <std::shared_ptr<Event>,
        std::vector<std::shared_ptr<Event>>,
        EventCompare> Events;

    /**
     * @brief T is the Topology over which the calls are generated.
     */
    std::shared_ptr<Topology> T;
    /**
     * @brief mu is the parameter for the call duration exponential distribution.
     */
    static constexpr double mu = 1;
    /**
     * @brief h is t parameter for the cl interarrival time exponential
     * distribution.
     */
    double h;
    /**
     * @brief simulationTime is the current time seen by the last call.
     */
    double simulationTime;
    /**
     * @brief Bitrates is a vector containing the possible bitrates.
     */
    std::vector<TransmissionBitrate> Bitrates;
    /**
     * @brief generate_Call chooses at random an origin, a destination, a bitrate
     * and creates a call. Its arrival time and duration are chosen with the
     * exponential distributions determined by h and mu.
     *
     * @return a shared_ptr to a Call.
     */
    std::shared_ptr<Call> generate_Call();
    /**
     * @brief set_Load is used to set a new value to the network load of this
     * Generator.
     * @param load is the new load, in Erlangs.
     */
    void set_Load(double load);

  private:
    //Distributions
    std::uniform_int_distribution<int> UniformNodeDistribution;
    std::uniform_int_distribution<int> UniformBitrateDistribution;
    std::exponential_distribution<double> ExponentialDistributionMu;
    std::exponential_distribution<double> ExponentialDistributionH;

};

#endif // CALLGENERATOR_H
