#ifndef CHOPDISTANCE_H
#define CHOPDISTANCE_H

#include "Cost.h"
#include <map>

namespace ROUT
{
namespace PSR
{

/**
 * @brief The cHopDistance class has, as cost, the distance between the call's
 * origin and destination nodes, measured in terms of how many links there are
 * in the route between them found by the minimum hops algorithm.
 */
class cHopDistance : public Cost
{
public:
    /**
     * @brief cHopDistance is the standard constructor for the cHopDistance cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cHopDistance(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);

private:
    void createCache();
    std::map<std::pair<int, int>, arma::rowvec> cache;

    struct Comparator
    {
        int OrigID;
        int DestID;
        double RouteLength;
        unsigned int NumHops;

        Comparator(int, int, double, unsigned int);
        bool operator <(const Comparator &) const;
    };
};

}
}

#endif // CHOPDISTANCE_H
