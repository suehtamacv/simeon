#ifndef CALLGENERATOR_H
#define CALLGENERATOR_H

#include <memory>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <Calls/Event.h>
#include <Structure/Topology.h>
#include <queue>

class CallGenerator {
  public:
    CallGenerator(Topology NetTopology, long double mu, long double h);

    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> Events;

    Topology NetTopology;
    long double mu;
    long double h;
    long double simulationTime;

    //Mersenne Twister Random Number Generator
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

    Call generate_Call();
};

#endif // CALLGENERATOR_H
