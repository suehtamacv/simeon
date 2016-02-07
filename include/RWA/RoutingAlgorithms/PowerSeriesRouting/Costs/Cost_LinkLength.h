#ifndef CLINKLENGTH_H
#define CLINKLENGTH_H

#include "Cost.h"
#include <map>

namespace PSR
{

class cLinkLength : public Cost
{
public:
    cLinkLength(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);

private:
    void createCache();
    std::map<std::shared_ptr<Link>, arma::rowvec> cache;

    struct Comparator
    {
        std::weak_ptr<Link> link;
        bool operator <(const Comparator &) const;
    };
};

}

#endif // CLINKLENGTH_H
