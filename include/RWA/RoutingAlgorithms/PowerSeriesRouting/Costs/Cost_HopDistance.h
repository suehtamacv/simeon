#ifndef CHOPDISTANCE_H
#define CHOPDISTANCE_H

#include "Cost.h"
#include <map>

namespace PSR
{

class cHopDistance : public Cost
{
public:
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

#endif // CHOPDISTANCE_H
