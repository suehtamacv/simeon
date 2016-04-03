#ifndef BITRATE_H
#define BITRATE_H

#include "Cost.h"
#include <map>
#include <GeneralClasses/TransmissionBitrate.h>

namespace ROUT
{
namespace PSR
{

/**
 * @brief The cBitrate class has, as cost, the bitrate of the call, normalized
 * by the greatest bitrate possible.
 */
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
}

#endif // BITRATE_H
