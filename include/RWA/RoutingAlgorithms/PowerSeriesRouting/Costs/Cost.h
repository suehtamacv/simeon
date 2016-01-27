#ifndef COST_H
#define COST_H

#include <memory>
#include <armadillo>
#include <boost/bimap.hpp>

class Link;
class Call;
class Topology;

namespace PSR
{

class Cost
{
public:
#define POSSIBLECOSTS \
    X(availability, "Availability", "availability", cAvailability) \
    X(bitrate, "Bitrate", "bitrate", cBitrate) \
    X(contiguity, "Contiguity", "contiguity", cContiguity) \
    X(distance, "Distance", "distance", cDistance) \
    X(noise, "Noise", "noise", cNoise) \
    X(normcontiguity, "Normalized Contiguity", "normcontiguity", cNormContiguity) \
    X(normnoise, "Normalized Noise", "normnoise", cNormNoise) \
    X(slots, "Number of Required Slots", "slots", cSlots) \
    X(occupability, "Occupability", "occupability", cOccupability) \
    X(scheme, "Modulation Scheme", "scheme", cModulationScheme)

#define X(a,b,c,d) a,
    enum PossibleCosts
    {
        POSSIBLECOSTS
    };
#undef X

    typedef boost::bimap<PossibleCosts, std::string> CostNameBimap;
    static CostNameBimap CostsNames;
    typedef boost::bimap<PossibleCosts, std::string> CostNicknameBimap;
    static CostNicknameBimap CostsNicknames;

    Cost(int NMin, int NMax, std::shared_ptr<Topology> T, PossibleCosts Type);
    virtual arma::rowvec getCost(std::weak_ptr<Link> link,
                                 std::shared_ptr<Call> C) = 0;
    static std::shared_ptr<Cost> createCost(PossibleCosts, int NMin, int NMax,
                                            std::shared_ptr<Topology>);

    int get_NMin();
    int get_NMax();
    int get_N();

    PossibleCosts Type;

protected:
    int NMin, NMax;
    std::shared_ptr<Topology> T;
};

}

#endif // COST_H
