#include <Calls/CallGenerator.h>
#include <Calls/Call.h>

boost::mt19937 CallGenerator::MersenneTwister;

CallGenerator::CallGenerator(std::shared_ptr<Topology> T,
                             long double h,
                             std::vector<TransmissionBitrate> Bitrates) :
    T(T), h(h), simulationTime(0), Bitrates(Bitrates) {

    //MersenneTwister = boost::mt19937(time(0)); Do not seed RNG

    UniformNodeDistribution = boost::uniform_int<>(0, T->Nodes.size() - 1);
    UniformBitrateDistribution = boost::uniform_int<>(0, Bitrates.size() - 1);
    ExponentialDistributionMu = boost::exponential_distribution<>(1.0 / mu);
    ExponentialDistributionH = boost::exponential_distribution<>(h);

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
    simulationTime = ArrivalTime;

    int Origin = (*UniformNodeGenerator)();
    int Destination = (*UniformNodeGenerator)();

    while (Origin == Destination) {
        Destination = (*UniformNodeGenerator)();
    }

    int Bitrate = (*UniformBitrateGenerator)();

    std::shared_ptr<Call> C(new Call(std::weak_ptr<Node>(T->Nodes.at(Origin)),
                                     std::weak_ptr<Node>(T->Nodes.at(Destination)),
                                     Bitrates[Bitrate]));

    std::shared_ptr<Event> CallRequisition(new Event(ArrivalTime,
                                           Event::CallRequisition, C));
    std::shared_ptr<Event> CallEnding(new Event(EndingTime,
                                      Event::CallEnding, C));

    Events.push(CallRequisition);
    Events.push(CallEnding);

    C->CallRequisition = CallRequisition;
    C->CallEnding = CallEnding;

    return C;
}
