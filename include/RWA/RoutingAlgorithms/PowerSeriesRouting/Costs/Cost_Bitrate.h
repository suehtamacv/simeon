#ifndef BITRATE_H
#define BITRATE_H

#include "Cost.h"
#include <map>
#include <GeneralClasses/TransmissionBitrate.h>

namespace PSR
{

class cBitrate : public Cost
{
public:
    cBitrate(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link>, std::shared_ptr<Call> C);

private:
    void createCache();
    std::map<TransmissionBitrate, arma::rowvec> cache;
};

}

#endif // BITRATE_H
