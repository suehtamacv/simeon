#ifndef CSLOTS_H
#define CSLOTS_H

#include "Cost.h"
#include <map>

namespace PSR
{

class cSlots : public Cost
{
public:
    cSlots(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link>, std::shared_ptr<Call>);

private:
    void createCache();
    std::map<unsigned int, arma::rowvec> cache;
};

}

#endif // CSLOTS_H
