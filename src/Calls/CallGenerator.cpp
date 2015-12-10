#include <Calls/CallGenerator.h>
#include <Calls/Call.h>

boost::mt19937 CallGenerator::MersenneTwister;

CallGenerator::CallGenerator(std::shared_ptr<Topology> T,
                             long double mu,
                             long double h,
                             std::vector<TransmissionBitrate> Bitrates) :
    T(T), mu(mu), h(h), simulationTime(0), Bitrates(Bitrates) {

    //MersenneTwister = boost::mt19937(time(0)); Do not seed RNG

    UniformNodeDistribution = boost::uniform_int<>(0, T->Nodes.size() - 1);
    UniformBitrateDistribution = boost::uniform_int<>(0, Bitrates.size() - 1);
    ExponentialDistributionMu = boost::exponential_distribution<>(mu);
    ExponentialDistributionH = boost::exponential_distribution<>(1.0 / h);

    UniformNodeGenerator =
        std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::uniform_int<> >>
        (new boost::variate_generator< boost::mt19937 , boost::uniform_int<> >
         (MersenneTwister, UniformNodeDistribution));
    UniformBitrateGenerator =
        std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::uniform_int<> >>
        (new boost::variate_generator< boost::mt19937 , boost::uniform_int<> >
         (MersenneTwister, UniformBitrateDistribution));
    ExponentialGeneratorMu =
        std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >>
        (new boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >
         (MersenneTwister, ExponentialDistributionMu));
    ExponentialGeneratorH =
        std::unique_ptr<boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >>
        (new boost::variate_generator< boost::mt19937 , boost::exponential_distribution<> >
         (MersenneTwister, ExponentialDistributionH));
}

std::shared_ptr<Call> CallGenerator::generate_Call() {
    long double ArrivalTime = simulationTime + (*ExponentialGeneratorH)();
    long double EndingTime = ArrivalTime + (*ExponentialGeneratorMu)();
    simulationTime += ArrivalTime;

    int Origin = (*UniformNodeGenerator)();
    int Destination = (*UniformNodeGenerator)();

    while (Origin == Destination) {
        Destination = (*UniformNodeGenerator)();
    }

    int Bitrate = (*UniformBitrateGenerator)();

    std::shared_ptr<Call> C(new Call(ArrivalTime, EndingTime,
                                     std::weak_ptr<Node>(T->Nodes.at(Origin)),
                                     std::weak_ptr<Node>(T->Nodes.at(Destination)), Bitrates[Bitrate]));
    Events.push(C->CallRequisition);
    Events.push(C->CallEnding);

    return C;
}
