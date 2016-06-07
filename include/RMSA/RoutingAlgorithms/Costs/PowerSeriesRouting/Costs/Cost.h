#ifndef COST_H
#define COST_H

#include <memory>
#include <armadillo>
#include <boost/bimap.hpp>

class Link;
class Call;
class Topology;

namespace RMSA
{
namespace ROUT
{
namespace PSR
{
/**
 * @brief The Cost class represents a cost to the PSR.
 */
class Cost
{
public:
#define POSSIBLECOSTS \
    X(availability, "Availability", "availability", cAvailability) \
    X(bitrate, "Bitrate", "bitrate", cBitrate) \
    X(contiguity, "Contiguity", "contiguity", cContiguity) \
    X(distance, "Distance", "distance", cDistance) \
    X(hopdistance, "Hop Distance", "hopdistance", cHopDistance) \
    X(linklength, "Link Length", "linklength", cLinkLength) \
    X(noise, "Noise", "noise", cNoise) \
    X(normcontiguity, "Normalized Contiguity", "normcontiguity", cNormContiguity) \
    X(slots, "Number of Required Slots", "slots", cSlots) \
    X(origdestindex, "Origin-Destination Index", "origdestindex", cOrigDestIndex) \
    X(occupability, "Occupability", "occupability", cOccupability) \
    X(scheme, "Modulation Scheme", "scheme", cModulationScheme)

#define X(a,b,c,d) a,
    /**
     * @brief The PossibleCosts enum represents the possible costs that are
     * implemented.
     */
    enum PossibleCosts
    {
        POSSIBLECOSTS
    };
#undef X

    typedef boost::bimap<PossibleCosts, std::string> CostNameBimap;
    static CostNameBimap CostsNames;
    typedef boost::bimap<PossibleCosts, std::string> CostNicknameBimap;
    static CostNicknameBimap CostsNicknames;

    /**
     * @brief Cost is the standard constructor.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     * @param Type is the type of cost.
     */
    Cost(int NMin, int NMax, std::shared_ptr<Topology> T, PossibleCosts Type);
    /**
     * @brief getCost returns a vector containing the cost, elevated to the
     * required exponents, in order.
     * @param link is the current link where the cost is being calculated.
     * @param C is the Call being routed.
     * @return a arma::rowvec with the costs, elevated to the required exponents.
     */
    virtual arma::rowvec getCost(std::weak_ptr<Link> link,
                                 std::shared_ptr<Call> C) = 0;
    /**
     * @brief getCost returns the cost, elevated to \a N.
     * @param N is the exponent.
     * @param link is the current link where the cost is being calculated.
     * @param C is the Call being routed.
     * @return a the cost, elevated to \a N.
     */
    double getCost(int N, std::weak_ptr<Link> link, std::shared_ptr<Call> C);
    /**
     * @brief createCost is used to create a cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @return a pointer to the cost.
     */
    static std::shared_ptr<Cost> createCost(PossibleCosts, int NMin, int NMax,
                                            std::shared_ptr<Topology>);

    /**
     * @brief get_NMin returns the minimum exponent.
     * @return the minimum exponent.
     */
    int get_NMin();
    /**
     * @brief get_NMax returns the maximum exponent.
     * @return the maximum exponent.
     */
    int get_NMax();
    /**
     * @brief get_N returns the number of exponents, i.e., the truncating point
     * of the power series.
     * @return the number of exponents.
     */
    int get_N();
    /**
     * @brief Type identifies the type of this cost.
     */
    PossibleCosts Type;

protected:
    int NMin, NMax;
    std::shared_ptr<Topology> T;
};
}
}
}

#endif // COST_H
