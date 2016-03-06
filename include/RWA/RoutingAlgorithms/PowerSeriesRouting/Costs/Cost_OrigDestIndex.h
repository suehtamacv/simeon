#ifndef CORIGDESTINDEX_H
#define CORIGDESTINDEX_H

#include <map>
#include "Cost.h"

namespace PSR
{
class cOrigDestIndex : public Cost
{
public:
    cOrigDestIndex(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link>, std::shared_ptr<Call>);

private:
    void createCache();
    std::map<std::pair<int, int>, arma::rowvec> cache;
};
}

#endif // CORIGDESTINDEX_H
