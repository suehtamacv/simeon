#include <Calls/CallGenerator.h>
#include <Calls/Call.h>
#include <Calls/Event.h>
#include <GeneralClasses/RandomGenerator.h>
#include <gtest/gtest.h>

bool CallGenerator::EventCompare::operator()(const std::shared_ptr<Event> a,
        const std::shared_ptr<Event> b) const
{
    return *a > *b;
}

CallGenerator::CallGenerator(std::shared_ptr<Topology> T,
                             double h,
                             std::vector<TransmissionBitrate> Bitrates) :
    T(T), h(h), simulationTime(0), Bitrates(Bitrates)
{

    UniformNodeDistribution = std::uniform_int_distribution<int>
                              (0, T->Nodes.size() - 1);
    UniformBitrateDistribution = std::uniform_int_distribution<int>
                                 (0, Bitrates.size() - 1);
    ExponentialDistributionMu = std::exponential_distribution<double>
                                (1.0L / mu);
    ExponentialDistributionH = std::exponential_distribution<double>(h);

}

std::shared_ptr<Call> CallGenerator::generate_Call()
{
    double ArrivalTime = simulationTime + ExponentialDistributionH(
                             random_generator);
    double EndingTime = ArrivalTime + ExponentialDistributionMu(random_generator);
    simulationTime = ArrivalTime;

    int Origin = UniformNodeDistribution(random_generator);
    int Destination = UniformNodeDistribution(random_generator);

    while (Origin == Destination)
        {
        Destination = UniformNodeDistribution(random_generator);
        }

    int Bitrate = UniformBitrateDistribution(random_generator);

    std::shared_ptr<Call> C(new Call(std::weak_ptr<Node>(T->Nodes[Origin]),
                                     std::weak_ptr<Node>(T->Nodes[Destination]),
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

void CallGenerator::set_Load(double h)
{
#ifdef RUN_ASSERTIONS
    EXPECT_GE(h, 0) << "Network loads must be positive.";
#endif
    this->h = h;
    ExponentialDistributionH = std::exponential_distribution<double>(h);
}
