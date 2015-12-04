#include <Calls/CallGenerator.h>
#include <Calls/Call.h>

boost::mt19937 CallGenerator::MersenneTwister;

CallGenerator::CallGenerator(Topology NetTopology, long double mu,
                             long double h) : NetTopology(NetTopology), mu(mu), h(h), simulationTime(0) {

    //MersenneTwister = boost::mt19937(time(0)); Do not seed RNG

    UniformDistribution = boost::uniform_int<>(0, NetTopology.numNodes - 1);
    ExponentialDistributionMu = boost::exponential_distribution<>(mu);
    ExponentialDistributionH = boost::exponential_distribution<>(1.0 / h);

    UniformGenerator =
        std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::uniform_int<> >>
        (new boost::variate_generator< boost::mt19937 , boost::uniform_int<> >
         (MersenneTwister, UniformDistribution));
    ExponentialGeneratorMu =
        std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >>
        (new boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >
         (MersenneTwister, ExponentialDistributionMu));
    ExponentialGeneratorH =
        std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >>
        (new boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >
         (MersenneTwister, ExponentialDistributionH));
}

Call CallGenerator::generate_Call() {
    long double ArrivalTime = simulationTime + (*ExponentialGeneratorH)();
    long double EndingTime = ArrivalTime + (*ExponentialGeneratorMu)();

    int Origin = (*UniformGenerator)();
    int Destination = (*UniformGenerator)();

    while (Origin == Destination) {
        Destination = (*UniformGenerator)();
    }

    Call C(ArrivalTime, EndingTime,
           std::weak_ptr<Node>(NetTopology.Nodes.at(Origin)),
           std::weak_ptr<Node>(NetTopology.Nodes.at(Destination)));
    Events.push(*C.CallRequisition);
    Events.push(*C.CallEnding);

    return C;
}
