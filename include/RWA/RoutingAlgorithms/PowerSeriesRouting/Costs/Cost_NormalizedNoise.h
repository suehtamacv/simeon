#ifndef CNORMNOISE_H
#define CNORMNOISE_H

#include "Cost.h"
#include <GeneralClasses/TransmissionBitrate.h>
#include <GeneralClasses/ModulationScheme.h>
#include <map>

namespace PSR
{

class cNormNoise : public Cost
{
public:
    cNormNoise(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

private:
    void createCache();
    std::map <std::shared_ptr<Link>, arma::rowvec> cache;
};

}

#endif // CNORMNOISE_H
